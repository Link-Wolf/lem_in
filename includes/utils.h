/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:31:48 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/23 11:28:26 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "./structures.h"
# include "./return_codes.h"
# include "./map_manipulation.h"
# include "../libft/libft.h"

/**
 *	@brief	Initialize the main room structure
 *  @param	lem_in		Pointer to the main room structure
 *	@note	Must call tini() to free it
 */
void	init(t_lem_in *lem_in);

/**
 *	@brief	Free the main room structure
 *	@param	lem_in		Pointer to the main room structure
 */
void	tini(t_lem_in *lem_in);

/**
 *	@brief	Print the error message corresponding to the code and exit
 *	@param	lem_in		Pointer to the main room structure
 *	@param	code		Error code
 */
void	bugs(t_lem_in *lem_in, int code);

/**
 *	@brief	Print the lem_in structure by calling the print functions for ants, rooms and links
 *	@param	lem_in		Pointer to the main room structure
 */
void	print_lemin(t_lem_in *lemin);

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
 *	@brief	Print all the paths ends
 */
void print_good_paths(t_lem_in *lem_in);

/**
 *	@brief	Delete a room and it's childrens
 *	@param	room	The room to delete
 */
void	delete_room(t_room *room);

/**
 *	@brief	Delete a path and it's childrens
 *	@param	path	The path to delete
 */
void	delete_pathes(t_pathes *path);

#endif
