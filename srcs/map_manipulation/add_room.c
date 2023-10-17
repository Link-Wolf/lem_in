/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:34:51 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/17 14:04:03 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map_manipulation.h"

int	add_room(t_room **rooms, char *name, int is_entry, int is_exit)
{
	t_room	*current_room;
	t_room	*previous_room;
	t_room	*new_room;
	int		name_comparaison;

	previous_room = NULL;
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
	new_room = new_room(name, is_entry, is_exit);
	if (!new_room)
		return (ERR_ALLOCATION);
	if (name_comparaison < 0)
		previous_room->left = new_room;
	if (name_comparaison > 0)
		previous_room->right = new_room;
	return (OK);
}
