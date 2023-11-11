/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:14:15 by Link           #+#    #+#             */
/*   Updated: 2023/11/11 15:30:49 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libs/libft/libft.h"
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
*/
void parse_file(t_mode mode);

/**
 * @brief      Processes the command line from the input
 * @param      line  The line to process
 * @param      cmd   The command to specify
*/
void process_cmd(char *line, int *cmd, t_mode mode);

/**
 * @brief      Processes the ants line from the input
 * @param      line   The line to process
 * @param      status The status of the parsing
 * @return     0 if everything went well, > 0 otherwise
*/
int process_ants(char *line, int *status, t_mode mode);

/**
 * @brief      Processes the rooms line from the input
 * @param      line   The line to process
 * @param      cmd    The potential command to take into account to process the room
 * @param      status The status of the parsing
*/
void process_rooms(char *line, int *cmd, int *status, t_mode mode);

/**
 * @brief      Processes the links line from the input
 * @param      line   The line to process
*/
void process_links(char *line, t_mode mode);

#endif
