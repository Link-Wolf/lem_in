/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:34:51 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/17 12:04:03 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map_manipulation.h"

int	add_room(t_room **rooms, char *name, int is_entry, int is_exit)
{
	t_room	*current_room;
	t_room	*previous_room;
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
	if (name_comparaison < 0)
		previous_room->left = new_room();
	if (name_comparaison > 0)
		previous_room->right = new_room();
	return (OK);
}
