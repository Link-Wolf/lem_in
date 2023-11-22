/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bugs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:20:02 by event             #+#    #+#             */
/*   Updated: 2023/11/22 14:03:54 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

const char	*error_msgs[] = {
	[OK] = "OK",
	[ERR_ROOM_ALREADY_EXISTS] = "Rooms cannot share the same name",
	[ERR_ALLOCATION] = "Cannot allocate memory",
	[ERR_ROOM_TYPE_CONFLICT] = "Room cannot be EXIT and start at the same time",
	[ERR_CMD_ROOM] = "Commands must be before a valide room declaration",
	[ERR_VALUE_ANTS] = "Ant value must be a valid positive integer",
	[ERR_ROOM_SYNTAX] = "Room declarations must follow the appropriate syntax",
	[ERR_SELF_LINKING_ROOM] = "Links cannot link a room to it self",
	[ERR_ROOM_DOES_NOT_EXIST] = "Links cannot link to unexisting rooms",
	[ERR_LINK_SYNTAX] = "Link declarations must follow the appropriate syntax",
	[ERR_NO_LINKS] = "The map is missing links",
	[ERR_CMD_LINK] = "Commands cannot be followed by links",
	[ERR_NO_START_END] = "The map is missing start and/or end room(s)",
	[ERR_LINK_ALREADY_EXISTS] = "Links cannot be duplicated",
	[ERR_NO_SOLUTION] = "No solution found, or we're fucked, or we're dumb, who knows",
	[ERR_USAGE] = "Usage: ./lemin [-v|--verbose] < map.map",
	[ERR_MLX_INIT] = "Error encountered while setting the MLX up",
	[ERR_MLX_NEW_IMG] = "Error encoutered while creating MLX Image",
	[ERR_MLX_IMG_TO_WIN] = "Error encountered while puting MLX Image to Window",
	[ERR_USAGE_BONUS] = "Usage: ./visualiser [-d|--debugger]"
};

void	bugs(int code)
{
	if (code != OK)
		ft_printf("ERROR %d: %s\n", code, error_msgs[code]);
	tini();
	exit(code);
}


