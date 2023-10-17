/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:19:13 by event             #+#    #+#             */
/*   Updated: 2023/10/17 16:16:35 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/map_manipulation.h"

/**
 *	@brief	Add a link from src to dest
 *	@param	src		The room that is modified to add the link
 *	@param	dest	The room to point to
 *	@returns	0 if everything went OK, -1 elsewise
 */
int		create_link(t_room *src, t_room *dest);
t_room	*find_room(t_room **rooms, char *name);

int	add_link(t_room **rooms, char *room1_name, char *room2_name)
{
	t_room	*room1;
	t_room	*room2;

	if (!ft_strcmp(room1_name, room2_name))
		return (ERR_SELF_LINKING_ROOM);
	room1 = find_room(rooms, room1_name);
	room2 = find_room(rooms, room2_name);
	if (room1 == NULL || room2 == NULL)
		return (ERR_ROOM_DONT_EXISTS);
	if (create_link(room1, room2) || create_link(room2, room1))
		return (ERR_ALLOCATION);
	return (OK);
}

int	create_link(t_room *src, t_room *dest)
{
	if (src->max_linked == src->nb_linked)
	{
		t_room	*new_linked = ft_calloc(src->max_linked * 2, sizeof (t_room));

		if (!new_linked)
			return (-1);
		ft_memcpy(new_linked, src->linked_rooms,
			sizeof (t_room) * src->max_linked * 2);
		src->max_linked *= 2;
		free(src->linked_rooms);
		src->linked_rooms = new_linked;
	}
	src->linked_rooms[src->nb_linked++] = dest;
	return (0);
}

t_room	*find_room(t_room **rooms, char *name)
{}
