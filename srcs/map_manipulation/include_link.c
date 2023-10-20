/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include_link.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:57:06 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/20 13:12:29 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/map_manipulation.h"

int	include_link(t_room **linked_rooms, t_room *room)
{
	while (*linked_rooms)
		if (*linked_rooms == room)
			return (1);
	return (0);
}
