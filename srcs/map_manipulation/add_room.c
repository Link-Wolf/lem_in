/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:34:51 by iCARUS            #+#    #+#             */
/*   Updated: 2023/11/01 11:04:16 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/map_manipulation.h"

/**
 *	@brief	Create a new room
 *	@param	name	The name of the room
 *	@param	is_start	Used as a boolean, indicate if the room is the start
 *	@param	is_end		Used as a boolean, indicate if the room is the end
 *	@returns	The newly allocated room filled
 */
static t_room	*create_room(char *name, int is_start, int is_end, int x_coord, int y_coord, int id);

int	add_room(t_lem_in *lem_in, char *name, int is_start, int is_end, int x_coord, int y_coord)
{
	t_room	*current_room;
	t_room	*previous_room;
	t_room	*new_room;
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
		ft_printf("##start\n");
		lem_in->start = new_room;
	}
	if (new_room->is_end)
	{
		ft_printf("##end\n");
		lem_in->end = new_room;
	}
	ft_printf("%s %d %d\n", name, x_coord, y_coord);
	return (OK);
}

t_room	*create_room(char *name, int is_start, int is_end, int x_coord, int y_coord, int id)
{
	(void) x_coord;
	(void) y_coord;
	t_room	*ret;

	ret = ft_calloc(1, sizeof (t_room));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret->name, name, NAME_SIZE + 1);
	ret->is_start = is_start;
	ret->is_end = is_end;
	ret->id = id;
	ret->max_linked = 8;
	ret->y_coord = INT_MAX;
	ret->x_coord = x_coord;
	ret->linked_rooms = ft_calloc(8, sizeof (t_room));
	if (!ret->linked_rooms)
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}
