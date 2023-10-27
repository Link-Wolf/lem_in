/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:45:56 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/27 10:49:47 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/processing.h"

static int calc_dist(t_lem_in *lem_in, t_room *room, int dist, int nb_pseudo_ends, int pseudo_end_idx);
static int	is_ancestor(t_pathes *parent, t_room *room);

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

void	create_pathes(t_lem_in *lem_in)
{
	lem_in->pathes = ft_calloc(lem_in->end->nb_linked, sizeof (t_pathes *));
	lem_in->good_pathes = ft_calloc(lem_in->end->nb_linked, sizeof (t_pathes **));
	lem_in->nb_pathes_leaves = ft_calloc(lem_in->end->nb_linked, sizeof (int));
	lem_in->max_pathes_leaves = ft_calloc(lem_in->end->nb_linked, sizeof (int));
	if (!lem_in->pathes)
		bugs(lem_in, ERR_ALLOCATION);


	int nb_pathes = 0;
	for (int i = 0; i < lem_in->end->nb_linked ; i++)
	{
		lem_in->max_pathes_leaves[i] = 8;
		lem_in->good_pathes[i] = ft_calloc(lem_in->max_pathes_leaves[i] + 1, sizeof (t_pathes *));
		lem_in->pathes[i] = create_path(lem_in->end->linked_rooms[i], i, NULL, 1, lem_in);

		//print good pathes
		ft_printf("End %d:\n", i);
		for (int j = 0; j < lem_in->nb_pathes_leaves[i]; j++)
		{
			ft_printf("\t\t");
			nb_pathes++;
			t_pathes *tmp = lem_in->good_pathes[i][j];
			while (tmp)
			{
				ft_printf("%s->", tmp->room->name);
				tmp = tmp->parent;
			}
			ft_printf("\n");
		}
	}
	ft_printf("\n\tNB PATHES : %d\n\tNB ROOMS : %d\n\tNB LINKS : %d\n\tNB START : %d\n\tNB EXIT : %d\n\n", nb_pathes, lem_in->nb_rooms, lem_in->nb_links, lem_in->start->nb_linked, lem_in->end->nb_linked);
}

t_pathes	*create_path(t_room *room, int end_index, t_pathes *parent, int depth, t_lem_in *lem_in)
{
	//create a path linked to a specific end, and recursively all other potential paths linked to this same end
	t_pathes	*ret;

	ret = ft_calloc(1, sizeof (t_pathes));
	ret->max_children = 8;
	ret->children = ft_calloc(ret->max_children + 1, sizeof (t_pathes *));
	ret->room = room;

	// Check all my linked rooms for start
	for (int i = 0 ; i < room->nb_linked; i++)
	{
		if (room->linked_rooms[i]->is_start)
			{
				ret->is_motherfucking_good = 1;
				ret->depth = depth;

				// NOTE: allocate more space if needed
				if (lem_in->nb_pathes_leaves[end_index] >= lem_in->max_pathes_leaves[end_index])
				{
					lem_in->max_pathes_leaves[end_index] *= 2;
					t_pathes **tmp = malloc((lem_in->max_pathes_leaves[end_index] + 1) * sizeof (t_pathes **));
					ft_memcpy(tmp, lem_in->good_pathes[end_index], lem_in->nb_pathes_leaves[end_index] * sizeof (t_pathes **));
					free(lem_in->good_pathes[end_index]);
					lem_in->good_pathes[end_index] = tmp;
				}
				lem_in->good_pathes[end_index][lem_in->nb_pathes_leaves[end_index]++] = ret;
				return (ret);
			}
	}
	// Add my linked room to struct if needed
	for (int i = 0 ; i < room->nb_linked ; i++)
	{
		// int my_distance = room->distances_to_ends[end_index];
		// int child_distance = room->linked_rooms[i]->distances_to_ends[end_index];
		int is_my_ancestor = is_ancestor(parent, room->linked_rooms[i]);
		if (!is_my_ancestor && !room->linked_rooms[i]->is_end)
		{
			t_pathes *new_path = create_path(room->linked_rooms[i], end_index, ret, depth + 1, lem_in);
			if (!new_path)
				continue;
			if (ret->nb_children == ret->max_children)
			{
				ret->max_children *= 2;
				t_pathes **real = ft_calloc(ret->max_children + 1, sizeof (t_pathes *));
				if (!real)
				{
					free(ret->children);
					free(ret);
					bugs(lem_in, ERR_ALLOCATION);
				}
				ft_memcpy(real, ret->children, ret->nb_children * sizeof(t_pathes));
				free(ret->children);
				ret->children = real;
			}
			new_path->parent = ret;
			ret->children[ret->nb_children] = new_path;
			ret->nb_children++;
		}
	}
	if (!ret->nb_children)
	{
		free(ret->children);
		free(ret);
		return (NULL);
	}
	return (ret);
}

static int	is_ancestor(t_pathes *parent, t_room *room)
{
	if (!parent)
		return (0);
	if (parent->room == room)
		return (1);
	return (is_ancestor(parent->parent, room));
}
