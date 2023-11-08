/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:31:48 by iCARUS            #+#    #+#             */
/*   Updated: 2023/11/08 15:35:26 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "./structures.h"
# include "./return_codes.h"
# include "./map_manipulation.h"
# include "../libs/libft/libft.h"

/**
 *	@brief	Initialize the main room structure
 *	@note	Must call tini() to free it
 */
void	init();

/**
 *	@brief	Free the main room structure
 */
void	tini();

/**
 *	@brief	Print the error message corresponding to the code and exit
 *	@param	code		Error code
 */
void	bugs(int code);

/**
 *	@brief	Print the lem_in structure by calling the print functions for ants, rooms and links
 */
void	print_lemin();

/**
 *	@brief	Print all the rooms recursively
 *	@param	room	The parent room of all rooms to print
 */
void	print_rooms(t_room *room);

/**
 *	@brief	Print all the links of all the rooms (both directions are printed)
 *	@param	room	The parent room of all rooms to print
 */
void	print_links(t_room *room);

/**
 *	@brief	Delete a room and it's childrens
 *	@param	room	The room to delete
 */
void	delete_room(t_room *room);

#endif
