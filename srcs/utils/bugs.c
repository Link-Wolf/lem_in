/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bugs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:20:02 by event             #+#    #+#             */
/*   Updated: 2023/10/20 11:38:20 by iCARUS           ###   ########.fr       */
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
};

void	bugs(t_lem_in *lem_in, int code)
{
	ft_printf("ERROR %d: %s\n", code, error_msgs[code]);
	tini(lem_in);
	exit(code);
}
