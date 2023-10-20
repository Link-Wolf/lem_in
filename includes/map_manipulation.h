/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_manipulation.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:42:25 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/20 11:49:53 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_MANIPULATION_H
# define MAP_MANIPULATION_H

# include "../libft/libft.h"

# include "return_codes.h"
# include "structures.h"

/**
 *	@brief	Add a room to the structure of rooms
 *	@param	lem_in		The global lemin structure
 *	@param	name		The name of the new room
 *	@param	is_start	Used as a boolean, indicate if the room is the start
 *	@param	is_end		Used as a boolean, indicate if the room is the end
 *	@param	x_coord		The x coordinate of the room
 *	@param	y_coord		The y coordinate of the room
 *	@returns	The appropriate return code (or 0 if everything went OK)
*/
int		add_room(
			t_lem_in *lem_in,
			char *name,
			int is_start,
			int is_end,
			int x_coord,
			int y_coord
	);

/**
 *	@brief	Add a link between 2 rooms
 *	@param	rooms		The structure of rooms
 *	@param	room1_name	The name of the first room
 *	@param	room2_name	The name of the second room
 *	@returns	The appropriate return code (or 0 if everything went OK)
 */
int		add_link(t_room **rooms, char *room1_name, char *room2_name);

/**
 *	@brief	Delete a room and it's childrens
 *	@param	room	The room to delete
 */
void	delete_room(t_room *room);

#endif
