/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:34:51 by iCARUS            #+#    #+#             */
/*   Updated: 2023/11/12 16:12:41 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/map_manipulation.h"

extern t_lem_in *lem_in;

/**
 *	@brief	Create a new room
 *	@param	name	The name of the room
 *	@param	is_start	Used as a boolean, indicate if the room is the start
 *	@param	is_end		Used as a boolean, indicate if the room is the end
 *	@returns	The newly allocated room filled
 */
static t_room	*create_room(char *name, int is_start, int is_end, int x_coord, int y_coord, int id);
static t_node	*init_node(t_graph *graph, t_room *room);

int	add_room(char *name, int is_start, int is_end, int x_coord, int y_coord, t_mode mode)
{
	t_room	*current_room;
	t_room	*previous_room;
	t_room	*new_room;
	t_node	*in_node;
	t_node	*out_node;
	int		name_comparaison = 0;

	previous_room = NULL;
	current_room = *lem_in->rooms;
	if (is_start && is_end)
		return (ERR_ROOM_TYPE_CONFLICT);

		// Look over the tree to find the right place to insert the new room
	// (useful in the future to easily find a room by its name)
	while (current_room)
	{
		name_comparaison = ft_strcmp(current_room->name, name);
		previous_room = current_room;
		if (name_comparaison < 0)
		{
			current_room = current_room->left;
			continue ;
		}
		if (name_comparaison > 0)
		{
			current_room = current_room->right;
			continue ;
		}
		return (ERR_ROOM_ALREADY_EXISTS);
	}
	new_room = create_room(name, is_start, is_end, x_coord, y_coord, lem_in->nb_rooms++);
	if (!new_room)
		return (ERR_ALLOCATION);
	if (name_comparaison < 0)
		previous_room->left = new_room;
	else if (name_comparaison > 0)
		previous_room->right = new_room;
	else
		*lem_in->rooms = new_room;
	if (new_room->is_start)
	{
		if (mode == DEFAULT)
		ft_printf("##start\n");
		lem_in->start = new_room;
		in_node = NULL;
	}
	else
		in_node = init_node(lem_in->graph, new_room);
	if (new_room->is_end)
	{
		if (mode == DEFAULT)
		ft_printf("##end\n");
		lem_in->end = new_room;
		out_node = NULL;
	}
	else
		out_node = init_node(lem_in->graph, new_room);
	if (in_node && out_node)
		create_edge(in_node, out_node, lem_in->graph);
	else
	{
		if (out_node)
			lem_in->graph->source = out_node;
		else if (in_node)
			lem_in->graph->sink = in_node;
	}
	new_room->in_node = in_node;
	new_room->out_node = out_node;
	if (mode == DEFAULT)
		ft_printf("%s %d %d\n", name, x_coord, y_coord);
	return (OK);
}

static t_room	*create_room(char *name, int is_start, int is_end, int x_coord, int y_coord, int id)
{
	t_room	*ret;

	ret = ft_calloc(1, sizeof (t_room));
	if (!ret)
		bugs(ERR_ALLOCATION);
	ft_strlcpy(ret->name, name, NAME_SIZE + 1);
	ret->is_start = is_start;
	ret->is_end = is_end;
	ret->id = id;
	ret->max_linked = 8;
	ret->y_coord = -1;
	ret->og_y_coord = y_coord;
	ret->x_coord = x_coord;
	ret->linked_rooms = ft_calloc(8, sizeof (t_room));
	if (!ret->linked_rooms)
	{
		free(ret);
		bugs(ERR_ALLOCATION);
	}
	return (ret);
}

static t_node *init_node(t_graph *graph, t_room *room)
{
	t_node *node;
	t_node **tmp;

	node = malloc(sizeof(t_node));
	if (!node)
		bugs(ERR_ALLOCATION);
	node->max_outing_edge_count = 8;
	node->nb_outing_edges = 0;
	node->outing_edges = malloc(sizeof(t_edge *) * node->max_outing_edge_count); //malloc(8 * sizeof (t_edge *));
	if (!node->outing_edges)
		bugs(ERR_ALLOCATION);
	if (graph->nb_nodes == graph->max_node_count)
	{
		graph->max_node_count *= 2;
		tmp = malloc(sizeof (t_node *) * graph->max_node_count);
		if (!tmp)
			bugs(ERR_ALLOCATION);
		ft_memcpy(tmp, graph->nodes, sizeof(t_node *) * graph->nb_nodes);
		free(graph->nodes);
		graph->nodes = tmp;
	}
	node->room = room;
	graph->nodes[graph->nb_nodes++] = node;
	return (node);
}

void	create_edge(t_node *node_in, t_node *node_out, t_graph *graph)
{
	t_edge	*edge;
	t_edge	*reverse_edge;
	t_edge	**tmp;

	edge = malloc(sizeof (t_edge));
	if (!edge)
		bugs(ERR_ALLOCATION);
	edge->capacity = 1;
	edge->flow = 0;
	edge->residual_capacity = 0;
	edge->is_reversal_edge = 0;
	edge->depth = 0;
	edge->in = node_in;
	edge->out = node_out;
	edge->previous_edge = NULL;

	reverse_edge = malloc(sizeof (t_edge));
	if (!reverse_edge)
		bugs(ERR_ALLOCATION);
	reverse_edge->capacity = 1;
	reverse_edge->flow = 0;
	reverse_edge->residual_capacity = 0;
	reverse_edge->is_reversal_edge = 1;
	reverse_edge->depth = 0;
	reverse_edge->in = node_out;
	reverse_edge->out = node_in;
	reverse_edge->previous_edge = NULL;

	if (graph->nb_edges + 1 >= graph->max_edge_count)
	{
		graph->max_edge_count *= 2;
		tmp = malloc(sizeof (t_edge *) * graph->max_edge_count);
		if (!tmp)
			bugs(ERR_ALLOCATION);
		ft_memcpy(tmp, graph->edges, sizeof(t_edge *) * graph->nb_edges);
		free(graph->edges);
		graph->edges = tmp;
	}
	graph->edges[graph->nb_edges++] = edge;
	graph->edges[graph->nb_edges++] = reverse_edge;

	if (node_in->nb_outing_edges == node_in->max_outing_edge_count)
	{
		node_in->max_outing_edge_count *= 2;
		tmp = malloc(sizeof (t_edge *) * node_in->max_outing_edge_count);
		if (!tmp)
			bugs(ERR_ALLOCATION);
		ft_memcpy(tmp, node_in->outing_edges, sizeof(t_edge *) * node_in->nb_outing_edges);
		free(node_in->outing_edges);
		node_in->outing_edges = tmp;
	}
	node_in->outing_edges[node_in->nb_outing_edges++] = edge;

	if (node_out->nb_outing_edges == node_out->max_outing_edge_count)
	{
		node_out->max_outing_edge_count *= 2;
		tmp = malloc(sizeof (t_edge *) * node_out->max_outing_edge_count);
		if (!tmp)
			bugs(ERR_ALLOCATION);
		ft_memcpy(tmp, node_out->outing_edges, sizeof(t_edge *) * node_out->nb_outing_edges);
		free(node_out->outing_edges);
		node_out->outing_edges = tmp;
	}
	node_out->outing_edges[node_out->nb_outing_edges++] = reverse_edge;
}
