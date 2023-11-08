/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:29:34 by iCARUS            #+#    #+#             */
/*   Updated: 2023/11/08 17:02:43 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/processing.h"

extern t_lem_in *lem_in;

static void 	set_null_flow(t_graph *graph);
static t_path 	*find_simple_path(t_graph *graph);
static int 		is_in_graph(t_edge *edge);
static t_edge	*find_antiparallele(t_edge *edge);
static void		init_queue(t_queue *queue);
static void		*pop_elem(t_queue *queue);
static void		push_elem(t_queue *queue, void *elem);


void	resolve()
{
	int		nb_pathes;
	int		nb_ants;
	int		delta;
	t_graph	*graph;
	t_path	*gamma;
	t_edge	*edge;

	nb_ants = lem_in->nb_ants;
	nb_pathes = 0;

	//	Contains all edges and the way they are organised,
	//		even the ones that doen't exists yet but will be used later
	//		as "reverse edge"
	graph = lem_in->graph;

	set_null_flow(graph); // Set all flows to 0
	// While we need path
	//	And we find a graph in the Residual graph
	while (nb_pathes <= nb_ants && (gamma = find_simple_path(graph)))
	{
		delta = 1; // 1 because all edges have capacity 1

		//	loop over all edges that compose the path gamma
		edge = gamma->last_edge;
		while (edge)
		{
			// If the edge is a normal edge
			if (is_in_graph(edge))
				edge->flow += delta;
			else // If the edge is a undo edge
				edge->flow -= delta;
			edge = edge->previous_edge;
		}
	}
}

static void set_null_flow(t_graph *graph)
{
	for (int i = 0 ; i < graph->nb_edges ; i++)
		graph->edges[i]->flow = 0;
}

static t_path *find_simple_path(t_graph *graph)
{
	//	Find a path in the residual graph
	//		Using BFS
	//		And return it

	t_path	*path;
	t_edge	*source;
	t_edge	*edge;
	t_queue	queue;

	path = NULL;
	source = NULL;
	edge = NULL;
	init_queue(&queue);

	// set all edges of the graph depth to 0 and previous edge to null
	for (int i = 0 ; i < graph->nb_edges ; i++)
	{
		graph->edges[i]->depth = 0;
		graph->edges[i]->previous_edge = NULL;
		graph->edges[i]->residual_capacity = is_in_graph(graph->edges[i])
			? graph->edges[i]->capacity - graph->edges[i]->flow
			: ((find_antiparallele(graph->edges[i]))->flow);
		/*
		 *	(capacity - flow)								si edge is in graph
		 *	flow of the antiparrelle						if not
		 */
	}

	// Add all entry exiting edges to the queue
	for (int i = 0 ; i < graph->source->nb_outing_edges ; i++)
	{
		if (graph->source->outing_edges[i]->residual_capacity <= 0)
			continue;
		edge = graph->source->outing_edges[i];
		edge->previous_edge = NULL;
		push_elem(&queue, edge);
	}

	while ((source = pop_elem(&queue)))
	{
		// loop over all edges in source->out->outing_edges
		for (int i = 0 ; i < source->out->nb_outing_edges ; i++)
		{
			if (edge->residual_capacity <= 0)
				continue;
			if (edge->out == graph->sink)
			{
				path = malloc(sizeof (t_path));
				path->last_edge = edge;
				return (path);
			}
			if (edge->depth == 0)
			{
				edge->depth = source->depth + 1;
				push_elem(&queue, edge);
				edge->previous_edge = source;
			}
		}
	}
	return (NULL);
}

static t_edge *find_antiparallele(t_edge *edge)
{
	for (int i = 0 ; i < edge->out->nb_outing_edges ; i++)
	{
		if (edge->out->outing_edges[i]->out == edge->in)
			return (edge->out->outing_edges[i]);
	}
	return (NULL);
}

static int is_in_graph(t_edge *edge)
{
	return (!edge->is_reversal_edge);
}

static void	init_queue(t_queue *queue)
{
	queue->allocated_space = 8;
	queue->elements = malloc(queue->allocated_space * sizeof (void *));
	queue->first_element_index = 0;
	queue->size = 0;
}

static void	*pop_elem(t_queue *queue)
{
	if (queue->first_element_index >= queue->size)
		return (NULL);
	return (queue->elements[queue->first_element_index++]);
}

static void push_elem(t_queue *queue, void *elem)
{
	void	**tmp;

	if (queue->size == queue->allocated_space)
	{
		queue->allocated_space *= 2;
		tmp = malloc(queue->allocated_space * sizeof (void *));
		ft_memcpy(tmp, queue->elements, queue->size * sizeof (void *));
		free(queue->elements);
		queue->elements = tmp;
	}
	queue->elements[queue->size++] = elem;
}
