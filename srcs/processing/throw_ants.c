/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:18:09 by Link           #+#    #+#             */
/*   Updated: 2023/11/09 16:24:20 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/processing.h"

extern t_lem_in *lem_in;

// static int		make_ants_advance(t_ant *ants, int nb_ants_sent);
static void		fill_ultimate_definitive_edition_deluxe_master_path(t_ultimate_definitive_edition_deluxe_master_path *ant_pathes);
static void		delete_ultimate_definitive_edition_deluxe_master_path(t_ultimate_definitive_edition_deluxe_master_path *ant_pathes);
static t_room 	*find_next_room(t_ultimate_definitive_edition_deluxe_master_path *ant_pathes);

void throw_ants() {
	int														total_ants = lem_in->nb_ants;
	// int														nb_ants_sent;
	int														nb_turn;
	int														nb_ants_arrived;
	int														nb_pathes = 0;
	t_ant													*ants;
	t_ultimate_definitive_edition_deluxe_master_path		**ant_pathes;

	ants = malloc(sizeof(t_ant) * total_ants);
	if (!ants)
		bugs(ERR_ALLOCATION);

	for (int i = 0; i < lem_in->start->nb_linked; i++)
	{
		t_room	*pseudo_entry = lem_in->start->linked_rooms[i];
		t_edge	*inner_edge = NULL;
		for (int j = 0; j < pseudo_entry->in_node->nb_outing_edges; j++)
		{
			if (!pseudo_entry->in_node->outing_edges[j]->is_reversal_edge)
			{
				inner_edge = pseudo_entry->in_node->outing_edges[j];
				break;
			}
		}
		if (inner_edge && inner_edge->flow)
			nb_pathes++;
	}
	ant_pathes = malloc(sizeof(t_ultimate_definitive_edition_deluxe_master_path *) * nb_pathes);
	if (!ant_pathes)
		bugs(ERR_ALLOCATION);

	int k = 0;
	for (int i = 0; i < lem_in->start->nb_linked; i++)
	{
		t_room	*pseudo_entry = lem_in->start->linked_rooms[i];
		t_edge	*inner_edge = NULL;
		for (int j = 0; j < pseudo_entry->in_node->nb_outing_edges; j++)
		{
			if (!pseudo_entry->in_node->outing_edges[j]->is_reversal_edge)
			{
				inner_edge = pseudo_entry->in_node->outing_edges[j];
				break;
			}
		}
		if (inner_edge && inner_edge->flow)
		{
			ant_pathes[k] = malloc(sizeof(t_ultimate_definitive_edition_deluxe_master_path));
			if (!ant_pathes[k])
				bugs(ERR_ALLOCATION);
			ant_pathes[k++]->room = inner_edge->in->room;
		}
	}

	while (--k >= 0)
	{
		fill_ultimate_definitive_edition_deluxe_master_path(ant_pathes[k]);
	}

	// nb_ants_sent = 0;
	nb_turn = -1; // The first round is a init_round with no ant movement
	nb_ants_arrived = 0;
	while (nb_ants_arrived < total_ants)
	{
		ft_printf("[rpiy]");
	}
	free(ants);
	for (int i = 0; i < nb_pathes; i++)
		delete_ultimate_definitive_edition_deluxe_master_path(ant_pathes[i]);
	free(ant_pathes);
	if (lem_in->verbose)
		ft_printf("#Solved in %d turns fro %d ants for %d rooms\n", nb_turn, total_ants, lem_in->nb_rooms);
}

// static int	make_ants_advance(t_ant *ants, int nb_ants_sent)
// {
// 	int	arriving_count = 0;

// 	for (int i = 0; i < nb_ants_sent; i++)
// 	{
// 		if (ants[i].is_arrived)
// 			continue;
// 		ft_printf("L%d-%s ", i, ants[i].room_to_go->name);
// 		ants[i].current_room = ants[i].room_to_go;
// 		if (ants[i].current_room == lem_in->end)
// 		{
// 			arriving_count++;
// 			ants[i].is_arrived = 1;
// 			continue;
// 		}
// 		for (int j = 0; j < ants[i].current_room->out_node->nb_outing_edges; j++)
// 		{
// 			if (ants[i].current_room->out_node->outing_edges[j]->flow
// 				&& !ants[i].current_room->out_node->outing_edges[j]->is_reversal_edge)
// 			{
// 				ants[i].room_to_go
// 					= ants[i].current_room->out_node->outing_edges[j]->out->room;
// 				break;
// 			}
// 		}
// 	}
// 	ft_printf("\n");
// 	return (arriving_count);
// }

static void fill_ultimate_definitive_edition_deluxe_master_path(
	t_ultimate_definitive_edition_deluxe_master_path *ant_pathes
)
{
	int													size = 0;
	t_ultimate_definitive_edition_deluxe_master_path	*start_ptr = ant_pathes;
	t_room												*next_room = NULL;

	while ((next_room = find_next_room(ant_pathes)))
	{
		ft_printf("looping on the path %p \n", next_room);
		ant_pathes->next = malloc(sizeof (t_ultimate_definitive_edition_deluxe_master_path));
		ant_pathes->next->room = next_room;
		ant_pathes = ant_pathes->next;
		size++;
	}
	start_ptr->size = size;
}

static t_room *find_next_room(t_ultimate_definitive_edition_deluxe_master_path *ant_pathes)
{
	if (ant_pathes->room->is_end)
		return (NULL);
	for (int i = 0; i < ant_pathes->room->out_node->nb_outing_edges; i++)
	{
		t_edge *edge = ant_pathes->room->out_node->outing_edges[i];
		if (edge->is_reversal_edge || edge->flow <= 0)
			continue;
		return edge->out->room;
	}
	return (NULL);
}

static	void	delete_ultimate_definitive_edition_deluxe_master_path(
	t_ultimate_definitive_edition_deluxe_master_path *ant_pathes
)
{
	if (!ant_pathes)
		return ;
	delete_ultimate_definitive_edition_deluxe_master_path(ant_pathes->next);
	free(ant_pathes);
}
