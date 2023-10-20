/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include_link.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:57:06 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/20 15:50:21 by iCARUS           ###   ########.fr       */
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
