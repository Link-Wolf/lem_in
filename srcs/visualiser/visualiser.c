/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualiser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:35:13 by Link           #+#    #+#             */
/*   Updated: 2023/11/10 11:52:53 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualiser.h"

extern t_lem_in *lem_in;

static void	set_room_locations(t_room *room, int width, int height);

void visualise()
{
	mlx_t*			mlx;
	mlx_image_t*	img;
	mlx_image_t*	bg;
	t_zoom			zoom;

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "lem-in", true)))
		bugs(ERR_MLX_INIT);

	if (!(img = mlx_new_image(mlx, WIDTH, HEIGHT)))
		bugs(ERR_MLX_NEW_IMG);

	if (!(bg = mlx_new_image(mlx, WIDTH, HEIGHT)))
		bugs(ERR_MLX_NEW_IMG);

	for (uint32_t x = 0; x < bg->width; x++)
		for (uint32_t y = 0; y < bg->height; y++)
			set_pixel_color(
				get_pixel_address(bg, x, y),
				0x000000FF
			);

	t_param			params = {mlx, img, bg, &zoom, 0.0, 0};

	if (mlx_image_to_window(mlx, bg, 0, 0) == -1)
		bugs(ERR_MLX_IMG_TO_WIN);
	if (mlx_image_to_window(mlx, img, 0, 0) == -1)
		bugs(ERR_MLX_IMG_TO_WIN);

	mlx_close_hook(mlx, handle_window_close, mlx);
	mlx_key_hook(mlx, handle_inputs, &params);
	mlx_resize_hook(mlx, resize_window, &params);
	mlx_scroll_hook(mlx, scroll_handler, &params);
	mlx_loop_hook(mlx, loop_handler, &params);

	double virtual_width = lem_in->visualiser->max_x
		* ROOM_DIAMETER * 3 + ROOM_DIAMETER * 2 * 2;
	double virtual_height = (lem_in->visualiser->max_y + 1)
		* (SPACE_BETWEEN_LINES * ROOM_DIAMETER)
		+ ROOM_DIAMETER
		+ ROOM_DIAMETER * 2 * 2;
	set_room_locations(*lem_in->rooms, virtual_width, virtual_height);
	zoom.scroll_direction = 'y';
	zoom.scroll_mode = 's';
	zoom.height = virtual_height;
	zoom.width = virtual_width;
	zoom.x_offset = 0;
	zoom.y_offset = 0;
	zoom.zoom_ratio = (double) WIDTH / virtual_width;

	generate_image(mlx, &img, bg, &zoom);

	mlx_loop(mlx);
	mlx_terminate(mlx);

	return ;
}

static void	set_room_locations(t_room *room, int width, int height)
{
	if (!room)
		return ;
	set_room_locations(room->left, width, height);
	set_room_locations(room->right, width, height);
	if (room->is_end)
	{
		room->x_coord = width / 2; // Center of the virtual space
		room->y_coord = ROOM_DIAMETER * 2 + ROOM_DIAMETER / 2; // Top of the virtual space
		return ;
	}
	if (room->is_start)
	{
		room->x_coord = width / 2; // Center of the virtual space
		room->y_coord = height - ROOM_DIAMETER * 2 - ROOM_DIAMETER / 2; // Bottom of the virtual space
		return ;
	}
	int current_x = room->x_coord;
	int current_y = room->y_coord;
	int current_line_size = lem_in->visualiser->room_line_size[current_y];
	int nb_lines = lem_in->visualiser->max_y;

	if (current_line_size == 1)
		room->x_coord = width / 2; // Center of the virtual space
	else
		room->x_coord = ROOM_DIAMETER * 2 + ROOM_DIAMETER / 2 // Minimum x
			+ (width - ROOM_DIAMETER * 2 * 2 - ROOM_DIAMETER) // Empty space between the left and the right
				/ (current_line_size - 1) // Number of spaces between rooms
				* current_x; // Position of the room in the line
	room->y_coord = ROOM_DIAMETER * 2 + ROOM_DIAMETER / 2 // Minimum y
		+ (height - ROOM_DIAMETER * 2 * 2 - ROOM_DIAMETER) // Empty space between the top and the bottom
			/ (nb_lines + 1) // Number of spaces between lines, +1 instad of -1 because we want to count the first line and the last line
			* (current_y); // Line of the room + 1 because we want to count the first line
}

void	generate_image(mlx_t *mlx, mlx_image_t **img, mlx_image_t *bg, t_zoom *zoom)
{
	mlx_image_t	*tmp = *img;

	int	must_put_image = 0;
	srand(3141595);

	ft_bzero((*img)->pixels, sizeof (uint32_t) * (*img)->width * (*img)->height);
	if (mlx->width != (int) (*img)->width || mlx->height != (int) (*img)->height)
	{
		if (!(tmp = mlx_new_image(mlx, mlx->width, mlx->height)))
			bugs(ERR_MLX_NEW_IMG);
		must_put_image = 1;
	}

	draw_all_links(*lem_in->rooms, tmp, ROOM_DIAMETER, tmp->width, zoom);
	draw_all_rooms(*lem_in->rooms, tmp, ROOM_DIAMETER, tmp->width, zoom);

	if (must_put_image)
	{
		*img = tmp;
		mlx_image_to_window(mlx, bg, 0, 0);
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

