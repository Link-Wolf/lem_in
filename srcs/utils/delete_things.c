/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_things.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 10:51:40 by iCARUS            #+#    #+#             */
/*   Updated: 2023/11/11 14:03:36 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	delete_room(t_room *room)
{
	if (!room)
		return ;

	free(room->linked_rooms);
	delete_room(room->left);
	delete_room(room->right);
	free(room);
}
