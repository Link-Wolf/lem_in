/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:14:15 by Link           #+#    #+#             */
/*   Updated: 2023/10/17 15:16:33 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#include "../libft/libft.h"
#include "./structures.h"
#include "./init.h"
#include "./codes.h"

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

void parse_file(t_lem_in *lem_in);
void process_cmd(char *line, int *cmd);
int process_ants(t_lem_in *lemin, char *line);
void process_rooms(t_lem_in *lemin, char *line, int cmd);
void process_links(char *line);

#endif