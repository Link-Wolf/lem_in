/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_codes.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:00:01 by iCARUS            #+#    #+#             */
/*   Updated: 2023/11/12 13:46:26 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RETURN_CODES_H
# define RETURN_CODES_H

enum {
	OK = 0,
	ERR_ROOM_ALREADY_EXISTS,
	ERR_ALLOCATION,
	ERR_ROOM_TYPE_CONFLICT,
	ERR_CMD_ROOM,
	ERR_VALUE_ANTS,
	ERR_ROOM_SYNTAX,
	ERR_SELF_LINKING_ROOM,
	ERR_ROOM_DOES_NOT_EXIST,
	ERR_LINK_SYNTAX,
	ERR_NO_LINKS,
	ERR_CMD_LINK,
	ERR_NO_START_END,
	ERR_LINK_ALREADY_EXISTS,
	ERR_NO_SOLUTION,
	ERR_USAGE,
	ERR_MLX_INIT,
	ERR_MLX_NEW_IMG,
	ERR_MLX_IMG_TO_WIN,
	ERR_USAGE_BONUS
};

enum {
	VERBOSE = 1 << 0,
	VISUALIZER = 1 << 1,
	DEBUGGER = 1 << 2
};

#endif
