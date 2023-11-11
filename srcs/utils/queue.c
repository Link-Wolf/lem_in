/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:57:36 by iCARUS            #+#    #+#             */
/*   Updated: 2023/11/11 12:33:55 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	init_queue(t_queue *queue)
{
	queue->allocated_space = 8;
	queue->elements = malloc(queue->allocated_space * sizeof (void *));
	queue->first_element_index = 0;
	queue->size = 0;
}

void	*pop_elem(t_queue *queue)
{
	if (queue->first_element_index >= queue->size)
		return (NULL);
	return (queue->elements[queue->first_element_index++]);
}

void push_elem(t_queue *queue, void *elem)
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

void delete_queue(t_queue *queue)
{
	free(queue->elements);
}
