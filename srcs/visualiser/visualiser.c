/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualiser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:35:13 by Link           #+#    #+#             */
/*   Updated: 2023/10/30 17:43:18 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualiser.h"


void visualise(t_lem_in *lemin)
{
	mlx_t*			mlx;
	mlx_image_t*	img;
	t_zoom			zoom = {0.0, 0.0, 1.0};

	srand(time(NULL));
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "lem-in", true)))
		bugs(lemin, ERR_MLX_INIT);

	if (!(img = mlx_new_image(mlx, WIDTH, HEIGHT)))
		bugs(lemin, ERR_MLX_NEW_IMG);

	t_param			params = {lemin, mlx, img, &zoom, 0.0, 0};

	if (mlx_image_to_window(mlx, img, 0, 0) == -1)
		bugs(lemin, ERR_MLX_IMG_TO_WIN);

	mlx_close_hook(mlx, handle_window_close, mlx);
	mlx_key_hook(mlx, handle_inputs, mlx);
	mlx_resize_hook(mlx, resize_window, &params);
	mlx_scroll_hook(mlx, scroll_handler, &params);
	mlx_loop_hook(mlx, loop_handler, &params);

	generate_image(mlx, &img, &zoom, lemin);

	mlx_loop(mlx);
	mlx_terminate(mlx);

	return ;
}

void	generate_image(mlx_t *mlx, mlx_image_t **img, t_zoom *zoom, t_lem_in *lemin)
{
	mlx_image_t	*tmp = *img;

	int	must_put_image = 0;

	if (mlx->width != (int) (*img)->width || mlx->height != (int) (*img)->height)
	{
		if (!(tmp = mlx_new_image(mlx, mlx->width, mlx->height)))
			bugs(lemin, ERR_MLX_NEW_IMG);
		must_put_image = 1;
	}

	ft_memset(tmp->pixels, 0xFF, tmp->width * tmp->height * 4);

	int max_line_size = lemin->visualiser->max_x;
	int actual_space_between_rooms = SPACE_BETWEEN_ROOMS;
	while ((max_line_size + 1) * actual_space_between_rooms > mlx->width - max_line_size * 10)
		actual_space_between_rooms--;
	int max_room_size = (mlx->width - ((max_line_size + 1) * actual_space_between_rooms)) / max_line_size;
	int room_size = ft_min(max_room_size, DESIRED_ROOM_SIZE);

	// draw start links
	for (int i = 0 ; i < lemin->start->nb_linked ; i ++)
	{
		draw_link(
			tmp,
			zoom->x + mlx->width / 2,
			zoom->y + room_size + (lemin->visualiser->max_y + 1) * room_size * 3,
			zoom->x + mlx->width
				/ (lemin->visualiser->room_line_size[lemin->start->linked_rooms[i]->y_coord] + 1)
				* (lemin->start->linked_rooms[i]->x_coord + 1),
			zoom->y	+ room_size	+ lemin->start->linked_rooms[i]->y_coord * room_size * SPACE_BETWEEN_LINES,
			START_ROOM_COLOR
		);
	}
	// draw end links
	for (int i = 0 ; i < lemin->end->nb_linked ; i ++)
	{
		draw_link(
			tmp,
			zoom->x + mlx->width / 2,
			zoom->y +room_size,
			zoom->x + mlx->width
				/ (lemin->visualiser->room_line_size[lemin->end->linked_rooms[i]->y_coord] + 1)
				* (lemin->end->linked_rooms[i]->x_coord + 1),
			zoom->y +room_size + lemin->end->linked_rooms[i]->y_coord * room_size * SPACE_BETWEEN_LINES,
			EXIT_ROOM_COLOR
		);
	}
	// draw all others links
	draw_all_links(*lemin->rooms, tmp, room_size, lemin, tmp->width, zoom);

	// draw start room
	draw_room(
		tmp,
		zoom->x + mlx->width / 2,
		zoom->y + room_size + (lemin->visualiser->max_y + 1) * room_size * 3,
		room_size,
		START_ROOM_COLOR
	);
	// draw end room
	draw_room(tmp, zoom->x + mlx->width / 2, zoom->y + room_size, room_size, EXIT_ROOM_COLOR);
	// draw all others rooms
	draw_all_rooms(*lemin->rooms, tmp, room_size, lemin, tmp->width, zoom);

	if (must_put_image)
	{
		*img = tmp;
		mlx_image_to_window(mlx, tmp, 0, 0);
	}
}


int get_random_color(void)
{
	int r = rand() % 255;
	int g = rand() % 255;
	int b = rand() % 255;

	return (r << 24 | g << 16 | b << 8 | 0xFF);
}

