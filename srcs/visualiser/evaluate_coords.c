/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_coords.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:45:56 by iCARUS            #+#    #+#             */
/*   Updated: 2023/11/11 15:04:09 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualiser.h"

extern t_lem_in *lem_in;

static void calc_x(t_room *room, int *tmp);

void evaluate_coords()
{
	t_queue	queue;
	t_room	*room;
	int		*tmp;

	init_queue(&queue);

	lem_in->visualiser->nb_allocated_room_lines = 8;
	lem_in->visualiser->room_line_size
		= ft_calloc(sizeof (int), lem_in->visualiser->nb_allocated_room_lines);
	if (!lem_in->visualiser->room_line_size)
		bugs(ERR_ALLOCATION);

	lem_in->end->y_coord = 0;
	push_elem(&queue, lem_in->end);
	while ((room = pop_elem(&queue)))
	{
		if (lem_in->visualiser->max_y < room->y_coord)
			lem_in->visualiser->max_y = room->y_coord;
		if (lem_in->visualiser->max_y
			>= lem_in->visualiser->nb_allocated_room_lines)
		{
			lem_in->visualiser->nb_allocated_room_lines *= 2;
			tmp = ft_calloc(lem_in->visualiser->nb_allocated_room_lines, sizeof (int));
			ft_memcpy(tmp, lem_in->visualiser->room_line_size, lem_in->visualiser->nb_allocated_room_lines / 2 * sizeof (int));
			free(lem_in->visualiser->room_line_size);
			lem_in->visualiser->room_line_size = tmp;
		}
		lem_in->visualiser->room_line_size[room->y_coord]++;
		for (int i = 0; i < room->nb_linked; i++)
		{
			if (room->linked_rooms[i]->y_coord >= 0)
				continue;
			room->linked_rooms[i]->y_coord = room->y_coord + 1;
			push_elem(&queue, room->linked_rooms[i]);
		}
	}
	delete_queue(&queue);
	tmp = ft_calloc(lem_in->visualiser->nb_allocated_room_lines, sizeof (int));
	calc_x(lem_in->start, tmp);
	free(tmp);
}
static void calc_x(t_room *room, int *tmp)
{
	if (!room) return;
	calc_x(room->left, tmp);
	calc_x(room->right, tmp);
	if (room->y_coord == -1) return;
	room->x_coord = tmp[room->y_coord]++;
	if (room->x_coord > lem_in->visualiser->max_x)
		lem_in->visualiser->max_x = room->x_coord;
}
