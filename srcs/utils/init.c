/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:18:34 by iCARUS            #+#    #+#             */
/*   Updated: 2023/11/08 17:20:47 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

extern t_lem_in *lem_in;

void	init()
{
	lem_in = malloc(sizeof (t_lem_in));
	if (!lem_in)
		bugs(ERR_ALLOCATION);
	lem_in->end = NULL;
	lem_in->start = NULL;
	lem_in->nb_ants = 0;
	lem_in->verbose = 0;
	lem_in->nb_rooms = 0;
	lem_in->nb_links = 0;
	lem_in->graph = ft_calloc(1, sizeof (t_graph));
	lem_in->rooms = ft_calloc(1, sizeof (t_room *));
	lem_in->visualiser = ft_calloc(1, sizeof (t_visualiser));
	if (!lem_in->rooms || !lem_in->visualiser || !lem_in->graph)
		bugs(ERR_ALLOCATION);
	lem_in->graph->nb_nodes = 0;
	lem_in->graph->nb_edges = 0;
	lem_in->graph->max_edge_count = 8;
	lem_in->graph->max_node_count = 8;
	lem_in->graph->nodes = ft_calloc(lem_in->graph->max_node_count, sizeof (t_node *));
	lem_in->graph->edges = ft_calloc(lem_in->graph->max_edge_count, sizeof (t_edge *));
	if (!lem_in->graph->nodes || !lem_in->graph->edges)
		bugs(ERR_ALLOCATION);
	lem_in->graph->source = NULL;
	lem_in->graph->sink = NULL;
	lem_in->visualiser->room_line_size = NULL;
}

void	tini()
{
	delete_room(*(lem_in->rooms));
	free(lem_in->rooms);
	free(lem_in->visualiser->room_line_size);
	free(lem_in->visualiser);
	for (int i = 0 ; i < lem_in->graph->nb_edges; i++)
	{
		free(lem_in->graph->edges[i]);
	}
	free(lem_in->graph->edges);
	for (int i = 0 ; i < lem_in->graph->nb_nodes;i++)
	{
		free(lem_in->graph->nodes[i]->outing_edges);
		free(lem_in->graph->nodes[i]);
	}
	free(lem_in->graph->nodes);
	free(lem_in->graph);
	free(lem_in);
}
