/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:45:56 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/20 15:50:21 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/processing.h"

static int calc_dist(t_lem_in *lem_in, t_room *room, int dist, int nb_pseudo_ends, int pseudo_end_idx);

void evaluate_distances(t_lem_in *lem_in)
{
	//get nb sorties/entress to init array in t_rooms
	int		nb_pseudo_ends = lem_in->end->nb_linked;
	t_room	**pseudo_ends = lem_in->end->linked_rooms;

	int pseudo_end_idx = 0;
	while (*pseudo_ends) {

		if (calc_dist(lem_in, *pseudo_ends, 1, nb_pseudo_ends, pseudo_end_idx) < 0)
			bugs(lem_in, ERR_ALLOCATION);

		pseudo_ends++;
		pseudo_end_idx++;
	}
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
		t_room	**linked_rooms = room->linked_rooms;

		while (*linked_rooms)
		{
			calc_dist(lem_in, *linked_rooms, dist + 1, nb_pseudo_ends, pseudo_end_idx);
			linked_rooms++;
		}
	}
	return (0);
}
