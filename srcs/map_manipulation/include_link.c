/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include_link.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Link <Link@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:57:06 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/20 17:24:36 by Link          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/map_manipulation.h"

int	include_link(t_room **linked_rooms, t_room *room)
{
	if (!linked_rooms)
		return (0);
	while (*linked_rooms)
	{
		if (*linked_rooms == room)
			return (1);
		linked_rooms++;
	}
	return (0);
}
