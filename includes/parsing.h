/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: link <link@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:14:15 by Link           #+#    #+#             */
/*   Updated: 2023/10/18 14:29:26 by link             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include "./structures.h"
# include "./utils.h"
# include "./return_codes.h"
# include "./map_manipulation.h"

enum {
	NONE = 0,
	START = 1,
	END = 2
};

enum {
	ANTS = 0,
	ROOMS = 1,
	LINKS = 2
};

/**
 * @brief      Parses the input data
 * @param      lem_in  The lem_in global structure to fill
*/
void parse_file(t_lem_in *lem_in);

/**
 * @brief      Processes the command line from the input
 * @param      line  The line to process
 * @param      cmd   The command to specify
*/
void process_cmd(char *line, int *cmd);

/**
 * @brief      Processes the ants line from the input
 * @param      lemin  The lem_in global structure
 * @param      line   The line to process
 * @return     0 if everything went well, > 0 otherwise
*/
int process_ants(t_lem_in *lemin, char *line, int *status);

/**
 * @brief      Processes the rooms line from the input
 * @param      lemin  The lem_in global structure
 * @param      line   The line to process
 * @param      cmd    The potential command to take into account to process the room
*/
void process_rooms(t_lem_in *lemin, char *line, int *cmd, int *status);

/**
 * @brief      Processes the links line from the input
 * @param      lemin  The lem_in global structure
 * @param      line   The line to process
*/
void process_links(t_lem_in *lemin, char *line);

#endif