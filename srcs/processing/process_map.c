/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:45:56 by iCARUS            #+#    #+#             */
/*   Updated: 2023/11/01 10:56:36 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/processing.h"

static int calc_dist(t_lem_in *lem_in, t_room *room, int dist, int nb_pseudo_ends, int pseudo_end_idx);
static void calc_x(t_lem_in *lem_in, t_room *room, int *tmp);

void evaluate_distances(t_lem_in *lem_in)
{
	//get nb sorties/entress to init array in t_rooms
	int		nb_pseudo_ends = lem_in->end->nb_linked;
	t_room	**pseudo_ends = lem_in->end->linked_rooms;

	int pseudo_end_idx = 0;

	if (lem_in->has_visualizer)
	{
		lem_in->visualiser->room_line_size = ft_calloc(1, sizeof(int));
		lem_in->visualiser->nb_allocated_room_lines = 1;
		lem_in->visualiser->max_x = 0;
		lem_in->visualiser->max_y = 0;
	}

	while (*pseudo_ends) {

		if (calc_dist(lem_in, *pseudo_ends, 1, nb_pseudo_ends, pseudo_end_idx) < 0)
			bugs(lem_in, ERR_ALLOCATION);

		pseudo_ends++;
		pseudo_end_idx++;
	}
	if (lem_in->has_visualizer)
	{
		int *tmp = ft_calloc(lem_in->visualiser->max_y + 1, sizeof(int));
		if (!tmp)
			bugs(lem_in, ERR_ALLOCATION);
		calc_x(lem_in, lem_in->start, tmp);
		ft_memcpy(lem_in->visualiser->room_line_size, tmp, (lem_in->visualiser->max_y + 1) * sizeof(int));
		free(tmp);
	}
}

static void calc_x(t_lem_in *lem_in, t_room *room, int *tmp)
{
	if (!room) return;
	calc_x(lem_in, room->left, tmp);
	calc_x(lem_in, room->right, tmp);
	if (room->y_coord == INT_MAX) return;
	room->x_coord = tmp[room->y_coord]++;
	if (room->x_coord > lem_in->visualiser->max_x)
		lem_in->visualiser->max_x = room->x_coord;
}

static int calc_dist(t_lem_in *lem_in, t_room *room, int dist, int nb_pseudo_ends, int pseudo_end_idx)
{
	if (!room->distances_to_ends)
	{
		room->distances_to_ends = ft_calloc((nb_pseudo_ends + 1), sizeof(int));
		if (!room->distances_to_ends)
			return (-1);
		for (int i = 0; i < nb_pseudo_ends; i++)
		{
			room->distances_to_ends[i] = INT_MAX;
		}
	}
	if (room->distances_to_ends[pseudo_end_idx]
		&& dist < room->distances_to_ends[pseudo_end_idx]
		&& room != lem_in->start
		&& room != lem_in->end
		)
	{
		room->distances_to_ends[pseudo_end_idx] = dist;

		if (lem_in->has_visualizer)
		{
			if (room->y_coord > dist)
			{
				if (lem_in->visualiser->max_y < dist)
				{
					lem_in->visualiser->max_y = dist;
				}
				if (lem_in->visualiser->nb_allocated_room_lines < dist + 1)
				{
					int *tmp = ft_calloc(dist + 1, sizeof(int));
					if (!tmp)
						bugs(lem_in, ERR_ALLOCATION);
					ft_memcpy(tmp, lem_in->visualiser->room_line_size, lem_in->visualiser->nb_allocated_room_lines * sizeof(int));
					free(lem_in->visualiser->room_line_size);
					lem_in->visualiser->room_line_size = tmp;
					lem_in->visualiser->nb_allocated_room_lines = dist;
				}
				if (room->y_coord != INT_MAX)
					lem_in->visualiser->room_line_size[room->y_coord]--;
				lem_in->visualiser->room_line_size[dist]++;
				if (lem_in->visualiser->max_x < lem_in->visualiser->room_line_size[dist])
				{
					lem_in->visualiser->max_x = lem_in->visualiser->room_line_size[dist];
				}
				room->y_coord = dist;
			}
		}

		t_room	**linked_rooms = room->linked_rooms;

		while (*linked_rooms)
		{
			calc_dist(lem_in, *linked_rooms, dist + 1, nb_pseudo_ends, pseudo_end_idx);
			linked_rooms++;
		}
	}
	return (0);
}
