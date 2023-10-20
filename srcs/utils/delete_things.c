/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_things.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Link <Link@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 10:51:40 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/20 17:24:36 by Link          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

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

void	delete_pathes(t_pathes *path)
{
	if (!path)
		return ;
	t_pathes	**children = path->children;
	while (*children)
	{
		delete_pathes(*children);
		children++;
	}
	free(path->children);
	free(path);
}
