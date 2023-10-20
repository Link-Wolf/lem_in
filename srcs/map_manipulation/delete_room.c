/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_room.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 10:51:40 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/20 10:53:13 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/map_manipulation.h"

void	delete_room(t_room *room)
{
	if (!room)
		return ;
	delete_room(room->left);
	delete_room(room->right);
	free(room->linked_rooms);
	free(room);
}
