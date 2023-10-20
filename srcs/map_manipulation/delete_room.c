/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_room.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Link <Link@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 10:51:40 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/20 15:04:32 by Link          ###   ########.fr       */
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
	free(room->distances_to_ends);
	free(room);
}
