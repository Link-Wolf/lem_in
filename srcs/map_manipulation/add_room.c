/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:34:51 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/17 15:17:29 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map_manipulation.h"

/**
 *	@brief	Create a new room
 *	@param	name	The name of the room
 *	@param	is_entry	Used as a boolean, indicate if the room is the entry
 *	@param	is_exit		Used as a boolean, indicate if the room is the exit
 *	@returns	The newly allocated room filled
 */
static t_room	*create_room(char *name, int is_entry, int is_exit);

int	add_room(t_room **rooms, char *name, int is_entry, int is_exit)
{
	t_room	*current_room;
	t_room	*previous_room;
	t_room	*new_room;
	int		name_comparaison;

	previous_room = NULL;
	if (is_entry && is_exit)
		return (ERR_ROOM_TYPE_CONFLICT);
	while (current_room)
	{
		name_comparaison = ft_strcmp(current_room->name, name);
		previous_room = current_room;
		if (name_comparaison < 0)
		{
			current_room = current_room->left;
		}
		if (name_comparaison > 0)
		{
			current_room = current_room->right;
		}
		return (ERR_NAME_CONFLICT);
	}
	new_room = create_room(name, is_entry, is_exit);
	if (!new_room)
		return (ERR_ALLOCATION);
	if (name_comparaison < 0)
		previous_room->left = new_room;
	if (name_comparaison > 0)
		previous_room->right = new_room;
	return (OK);
}

t_room	*create_room(char *name, int is_entry, int is_exit)
{
	t_room	*ret;

	ret = ft_calloc(1, sizeof (t_room));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret->name, name, NAME_SIZE + 1);
	ret->is_entry = is_entry;
	ret->is_exit = is_exit;
	ret->max_linked = 8;
	ret->linked_rooms = ft_calloc(8, sizeof (t_room));
	if (!ret->linked_rooms)
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}
