/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_manipulation.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: link <link@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:42:25 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/18 12:31:55 by link             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_MANIPULATION_H
# define MAP_MANIPULATION_H

# include "../libft/libft.h"

# include "return_codes.h"
# include "structures.h"

/**
 *	@brief	Add a room to the structure of rooms
 *	@param	rooms		The structure of rooms
 *	@param	name		The name of the new room
 *	@param	is_entry	Used as a boolean, indicate if the room is the entry
 *	@param	is_exit		Used as a boolean, indicate if the room is the exit
 *	@param	x_coord		The x coordinate of the room
 *	@param	y_coord		The y coordinate of the room
 *	@returns	The appropriate return code (or 0 if everything went OK)
*/
int	add_room(t_room **rooms, char *name, int is_entry, int is_exit, int x_coord, int y_coord);
/**
 *	@brief	Add a link between 2 rooms
 *	@param	rooms		The structure of rooms
 *	@param	room1_name	The name of the first room
 *	@param	room2_name	The name of the second room
 *	@returns	The appropriate return code (or 0 if everything went OK)
 */
int	add_link(t_room **rooms, char *room1_name, char *room2_name);

#endif
