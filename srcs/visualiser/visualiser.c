/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualiser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:35:13 by Link           #+#    #+#             */
/*   Updated: 2023/10/27 17:38:21 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <MLX42/MLX42.h>
#include "../../includes/visualiser.h"

static void draw_all_rooms(t_room *room, mlx_image_t *img, int room_size, t_lem_in *lemin);

void visualise(t_lem_in *lemin)
{
	mlx_t*		mlx;
	mlx_image_t* img;

	// // Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "lem-in", true)))
		bugs(lemin, ERR_MLX_INIT);
	if (!(img = mlx_new_image(mlx, WIDTH, HEIGHT)))
		bugs(lemin, ERR_MLX_NEW_IMG);

	//get output du lem_in
	//parcoure les rooms pour store min et max x et y
	//reparcoure des rooms pour afficher dans mlx_image
	//parcour des liens pour afficher dans same mlx_image
	//aff image
	// (aff ants turn by turn with delay etc... using pixel put)

	int max_line_size = lemin->visualiser->max_x; //TODO : verify

	int actual_space_between_rooms = SPACE_BETWEEN_ROOMS;
	while ((max_line_size + 1) * actual_space_between_rooms > WIDTH - max_line_size * 10)
		actual_space_between_rooms--;
	int max_room_size = (WIDTH - ((max_line_size + 1) * actual_space_between_rooms)) / max_line_size;
	int room_size = ft_min(max_room_size, DESIRED_ROOM_SIZE);

	ft_printf("max_room_size = %d\nroom_size = %d\ndesired size = %d\n", max_room_size, room_size, DESIRED_ROOM_SIZE);

	// draw start
	draw_room(
		img,
		WIDTH / 2,
		room_size + (lemin->visualiser->max_y + 1) * room_size * 3,
		room_size,
		0xFF0000FF
	);

	// draw all others
	// loop over all lines
	draw_all_rooms(*lemin->rooms, img, room_size, lemin);

	// draw end
	draw_room(img, WIDTH / 2, room_size, room_size, 0x0000FFFF);

	if (mlx_image_to_window(mlx, img, 0, 0) == -1)
		bugs(lemin, ERR_MLX_IMG_TO_WIN);
	mlx_loop(mlx);
	mlx_terminate(mlx);

	return ;
}

static void draw_all_rooms(t_room *room, mlx_image_t *img, int room_size, t_lem_in *lemin)
{
	if (room->left)
		draw_all_rooms(room->left, img, room_size, lemin);
	if (room->right)
		draw_all_rooms(room->right, img, room_size, lemin);
	if (room->is_start || room->is_end)
		return ;
	draw_room(
		img,
		WIDTH / (lemin->visualiser->room_line_size[room->y_coord] + 1) * (room->x_coord + 1),
		room_size + room->y_coord * room_size * 3,
		room_size,
		0xFFFFFFFF
	);
}