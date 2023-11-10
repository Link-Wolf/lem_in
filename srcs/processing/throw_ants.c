/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:18:09 by Link           #+#    #+#             */
/*   Updated: 2023/11/10 11:06:28 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/processing.h"

extern t_lem_in *lem_in;

static int		make_ants_advance(t_ant *ants, int nb_ants_sent, t_mode silent);
static void		fill_ultimate_definitive_edition_deluxe_master_path(t_ultimate_definitive_edition_deluxe_master_path *ant_pathes);
static void		delete_ultimate_definitive_edition_deluxe_master_path(t_ultimate_definitive_edition_deluxe_master_path *ant_pathes);
static t_room 	*find_next_room(t_ultimate_definitive_edition_deluxe_master_path *ant_pathes);
static int calc_min(t_ultimate_definitive_edition_deluxe_master_path **ant_pathes, int nb_pathes);
static void	sort_ant_pathes(t_ultimate_definitive_edition_deluxe_master_path **ant_pathes, int nb_pathes);
static void 	init_ant_path_send(t_ultimate_definitive_edition_deluxe_master_path **ant_pathes, int nb_pathes, int total_ants);

int throw_ants(t_mode mode) {
	int														total_ants = lem_in->nb_ants;
	int														nb_ants_sent;
	int														nb_turn;
	int														nb_ants_arrived;
	int														nb_pathes = 0;
	t_ant													*ants;
	t_ultimate_definitive_edition_deluxe_master_path		**ant_pathes;

	if (lem_in->verbose && mode == DEFAULT)
		ft_printf("# There are %d ants.\n", total_ants);

	ants = malloc(sizeof(t_ant) * total_ants);
	if (!ants)
		bugs(ERR_ALLOCATION);
	for (int i = 0; i < lem_in->graph->source->nb_outing_edges; i++)
	{
		t_edge *edge = lem_in->graph->source->outing_edges[i];
		if (edge->flow)
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

	sort_ant_pathes(ant_pathes, nb_pathes);

	init_ant_path_send(ant_pathes, nb_pathes, total_ants);

	nb_ants_sent = 0;
	nb_turn = -1; // The first round is a init_round with no ant movement
	nb_ants_arrived = 0;
	if (lem_in->verbose && mode == DEFAULT)
		for (int i = 0; i < nb_pathes; i++)
		{
			ft_printf("# Path of %d that starts on %s\n", ant_pathes[i]->size, ant_pathes[i]->room->name);
		}

	while (nb_ants_arrived < total_ants)
	{
		nb_ants_arrived += make_ants_advance(ants, nb_ants_sent, mode);
		for (int i = 0; i < nb_pathes; i++)
		{
			// ft_printf("%s : %d ; ", ant_pathes[i]->room->name , ant_pathes[i]->ants);
			if (nb_ants_sent >= total_ants)
				break;
			if (ant_pathes[i]->ants)
			{
				ants[nb_ants_sent].path = ant_pathes[i];
				ants[nb_ants_sent].is_arrived = 0;
				ant_pathes[i]->ants--;
				nb_ants_sent++;
			}
		}
		if (mode == DEFAULT)
		ft_printf("\n");
		nb_turn++;
	}

	free(ants);
	for (int i = 0; i < nb_pathes; i++)
		delete_ultimate_definitive_edition_deluxe_master_path(ant_pathes[i]);
	free(ant_pathes);
	if (lem_in->verbose && mode == DEFAULT)
		ft_printf("#Solved in %d turns fro %d ants for %d rooms\n", nb_turn, total_ants, lem_in->nb_rooms);
	return (nb_turn);
}

static int calc_min(t_ultimate_definitive_edition_deluxe_master_path **ant_pathes, int nb_pathes)
{
	int min = INT_MAX;

	for (int i = 0; i < nb_pathes; i++)
	{
		if (ant_pathes[i]->size + ant_pathes[i]->ants < min)
			min = ant_pathes[i]->size + ant_pathes[i]->ants;
	}
	return (min);
}

static int	make_ants_advance(t_ant *ants, int nb_ants_sent, t_mode mode)
{
	int	arriving_count = 0;

	for (int i = 0; i < nb_ants_sent; i++)
	{
		if (ants[i].is_arrived)
		{
			if (lem_in->verbose && mode == DEFAULT)
				ft_printf("          ");
			continue;
		}
		if (mode == DEFAULT)
		{
			if (lem_in->verbose)
				ft_printf("L%03d-%s ", i + 1, ants[i].path->room->name);
			else
				ft_printf("L%d-%s ", i + 1, ants[i].path->room->name);
		}
		if (ants[i].path->room->is_end || !ants[i].path->next)
		{
			arriving_count++;
			ants[i].is_arrived = 1;
			continue;
		}
		ants[i].path = ants[i].path->next;
	}
	if (mode == DEFAULT)
		ft_printf("\n");
	return (arriving_count);
}

static void fill_ultimate_definitive_edition_deluxe_master_path(
	t_ultimate_definitive_edition_deluxe_master_path *ant_pathes
)
{
	int													size = 0;
	t_ultimate_definitive_edition_deluxe_master_path	*start_ptr = ant_pathes;
	t_room												*next_room = NULL;

	while ((next_room = find_next_room(ant_pathes)))
	{
		ant_pathes->next = malloc(sizeof (t_ultimate_definitive_edition_deluxe_master_path));
		ant_pathes->next->room = next_room;
		ant_pathes = ant_pathes->next;
		size++;
	}
	ant_pathes->next = NULL;
	start_ptr->size = size;
	start_ptr->ants = 0;
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
	t_ultimate_definitive_edition_deluxe_master_path *tmp;

	while (ant_pathes && ant_pathes->next)
	{
		tmp = ant_pathes;
		ant_pathes = ant_pathes->next;
		free(tmp);
	}
	free(ant_pathes);
}

static void	sort_ant_pathes(t_ultimate_definitive_edition_deluxe_master_path **ant_pathes, int nb_pathes)
{
	int i, j;
	t_ultimate_definitive_edition_deluxe_master_path *key;
    for (i = 1; i < nb_pathes; i++) {
        key = ant_pathes[i];
        j = i - 1;

        /* Move elements of ant_pathes[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && ant_pathes[j]->size > key->size) {
            ant_pathes[j + 1] = ant_pathes[j];
            j = j - 1;
        }
        ant_pathes[j + 1] = key;
    }
}

static void 	init_ant_path_send(t_ultimate_definitive_edition_deluxe_master_path **ant_pathes, int nb_pathes, int total_ants)
{
	while (total_ants)
	{
		int min = calc_min(ant_pathes, nb_pathes);
		for (int i = 0; i < nb_pathes; i++)
		{
			if (!total_ants)
				break;
			if (ant_pathes[i]->size + ant_pathes[i]->ants == min)
			{
				ant_pathes[i]->ants++;
				total_ants--;
			}
		}
	}
}
