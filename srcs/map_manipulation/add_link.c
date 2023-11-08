/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:19:13 by event             #+#    #+#             */
/*   Updated: 2023/11/08 16:46:48 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/map_manipulation.h"

extern t_lem_in *lem_in;

/**
 *	@brief	Add a link from src to dest
 *	@param	src		The room that is modified to add the link
 *	@param	dest	The room to point to
 *	@returns	0 if everything went OK, -1 elsewise
 */
static int		create_link(t_room *src, t_room *dest);
/**
 *	@brief	Find a room in the map
 *	@param	rooms	The map
 *	@param	name	The name of the room
 *	@returns	A pointer on the room, NULL if it doesn't exist
 */
static t_room	*find_room(t_room **rooms, char *name);

int	add_link(t_room **rooms, char *room1_name, char *room2_name)
{
	t_room	*room1;
	t_room	*room2;

	if (!ft_strcmp(room1_name, room2_name))
		return (ERR_SELF_LINKING_ROOM);
	room1 = find_room(rooms, room1_name);
	room2 = find_room(rooms, room2_name);
	if (room1 == NULL || room2 == NULL)
		return (ERR_ROOM_DOES_NOT_EXIST);
	if (create_link(room1, room2) || create_link(room2, room1))
		return (ERR_ALLOCATION);
	ft_printf("%s-%s\n", room1_name, room2_name);
	return (OK);
}

static int	create_link(t_room *src, t_room *dest)
{
	if (include_link(src->linked_rooms, dest))
		return (ERR_LINK_ALREADY_EXISTS);
	if (src->nb_linked >= src->max_linked)
	{
		t_room	**new_linked = ft_calloc(src->max_linked * 2 + 1, sizeof (t_room *));
		if (!new_linked)
			bugs(ERR_ALLOCATION);
		ft_memcpy(new_linked, src->linked_rooms,
			sizeof (t_room *) * src->max_linked);
		src->max_linked *= 2;
		free(src->linked_rooms);
		src->linked_rooms = new_linked;
	}
	src->linked_rooms[src->nb_linked++] = dest;

	if (!dest->is_start && !src->is_end)
		create_edge(src->out_node, dest->in_node, lem_in->graph);
	if (!dest->is_end & !src->is_start)
		create_edge(dest->out_node, src->in_node, lem_in->graph);
	return (0);
}

static t_room	*find_room(t_room **rooms, char *name)
{
	t_room	*ret;
	int		cmp;

	ret = *rooms;
	while (ret && (cmp = ft_strcmp(ret->name, name)) != 0 && ret)
	{
		if (cmp > 0)
			ret = ret->right;
		else
			ret = ret->left;
	}
	return (ret);
}
