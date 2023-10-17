/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:48:40 by Link           #+#    #+#             */
/*   Updated: 2023/10/17 15:19:06 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void parse_file(t_lem_in *lem_in) {
	char	*line;
	int		status = ANTS;
	int		cmd = NONE;

	while ((line = get_next_line(0)) != NULL)
	{
		// Verify that the line following a command is a room
		if ((cmd == START || cmd == END) && (status != ROOMS || line[0] == '#'))
			bugs(lem_in, ERR_CMD_ROOM);
			
		// Case of commands and comments lines
		if (line[0] == '#')
		{
			if (line[1] && line[1] == '#') {
				process_cmd(line, &cmd);
			} else continue;
		}	
			
		// Case of ants, rooms and links lines
		if (status == ANTS)
			lem_in->nb_ants = process_ants(lem_in, line);
		else if (status == ROOMS)
			process_rooms(lem_in, line, &cmd);
		else if (status == LINKS)
			process_links(line);
	}
}

void process_rooms(t_lem_in *lemin, char *line, int *cmd) {
	//verify room syntax
	char *find = ft_strchr(line, ' ');
	if (find == NULL)
		bugs(lemin, ERR_ROOM_SYNTAX);

	int i = 0;
	char name[NAME_SIZE + 1];
	
	while (*find != *line && i < NAME_SIZE) {
		name[i] = *(line + i);
		i++;
	}
	name[i] = '\0';

	char *mid_coords = ft_strchr(find, ' ');
	
	//add room
	int ret = add_room(lemin->rooms, name, *cmd & START, *cmd & END);
	*cmd = NONE;
	if (ret > 0) {
		bugs(lemin, ret);
	}
}

void process_cmd(char *line, int *cmd) {
	if (ft_strcmp(line, "##start") == 0) 
		*cmd = START;
	else if (ft_strcmp(line, "##end") == 0)	
		*cmd = END;
}

int process_ants(t_lem_in *lemin, char *line) {
	int i = 0;

	while (line[i])	{
		if (!ft_isdigit(line[i]))
			bugs(lemin, ERR_VALUE_ANTS);
		i++;
	}
	return (ft_atoi(line));
}
