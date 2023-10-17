/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:48:40 by Link           #+#    #+#             */
/*   Updated: 2023/10/17 16:11:41 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static int verify_numbers(char *line);

void parse_file(t_lem_in *lem_in) {
	char	*line;
	int		status = ANTS;
	int		cmd = NONE;

	while ((line = get_next_line(0)) != NULL) {
		// Verify that the line following a command is a room
		if ((cmd == START || cmd == END) && (status != ROOMS || line[0] == '#'))
			bugs(lem_in, ERR_CMD_ROOM);
			
		// Case of commands and comments lines
		if (line[0] == '#')
		{
			if (line[1] && line[1] == '#')
				process_cmd(line, &cmd);
			else continue;
		}	
			
		// Case of ants, rooms and links lines
		if (status == ANTS)
			lem_in->nb_ants = process_ants(lem_in, line);
		else if (status == ROOMS)
			process_rooms(lem_in, line, &cmd);
		else if (status == LINKS)
			process_links(lem_in, line);
	}
}

void process_rooms(t_lem_in *lemin, char *line, int *cmd) {
	// Verify that the line contains a space after the name
	char *find = ft_strchr(line, ' ');
	if (find == NULL || find == line || find == line + 1)
		bugs(lemin, ERR_ROOM_SYNTAX);

	// Get the room name
	int i = 0;
	char name[NAME_SIZE + 1];
	
	while (*find != *line && i < NAME_SIZE) {
		name[i] = *(line + i);
		i++;
	}
	name[i] = '\0';

	// Get the room first coordinate
	i = 0;
	char coord[16];
	char *mid_coords = ft_strchr(find, ' ');
	if (mid_coords == NULL || mid_coords == find + 1)
		bugs(lemin, ERR_ROOM_SYNTAX);
	while (*mid_coords != *find) {
		coord[i] = *(find + i);
		i++;
	}
	coord[i] = '\0';
	if (verify_numbers(coord) || !ft_strlen(coord))
		bugs(lemin, ERR_ROOM_SYNTAX);

	// Get the room second coordinate
	i = 0;
	while (*mid_coords != '\0') {
		coord[i] = *(mid_coords + i);
		i++;
	}
	coord[i] = '\0';
	if (verify_numbers(coord) || !ft_strlen(coord))
		bugs(lemin, ERR_ROOM_SYNTAX);
	
	// Add the room to the structure
	int ret = add_room(lemin->rooms, name, *cmd & START, *cmd & END);
	*cmd = NONE;
	if (ret > 0)
		bugs(lemin, ret);
}

void process_links(t_lem_in *lemin, char *line) {
	// Verify that the line contains a dash
	char *find = ft_strchr(line, '-');
	if (find == NULL || find == line || find == line + 1)
		bugs(lemin, ERR_LINK_SYNTAX);

	// Get the first room name
	int i = 0;
	char name[NAME_SIZE + 1];
	
	while (*find != *line && i < NAME_SIZE) {
		name[i] = *(line + i);
		i++;
	}
	name[i] = '\0';

	// Get the second room name
	i++;
	int j = 0;
	char name2[NAME_SIZE + 1];
	while (line[i] != '\0') {
		name2[j] = *(line + i);
		i++;
		j++;
	}
	name2[j] = '\0';
	
	// Add the link to the structure
	int ret = add_link(lemin->rooms, name, name2);
	if (ret > 0)
		bugs(lemin, ret);
}

void process_cmd(char *line, int *cmd) {
	if (ft_strcmp(line, "##start") == 0) 
		*cmd = START;
	else if (ft_strcmp(line, "##end") == 0)	
		*cmd = END;
}

int process_ants(t_lem_in *lemin, char *line) {
	
	if (verify_numbers(line))
		bugs(lemin, ERR_VALUE_ANTS);
	return (ft_atoi(line));
}

static int verify_numbers(char *line) {
	int i = 0;

	while (line[i])	{
		if (!ft_isdigit(line[i]))
			return 1;
		i++;
	}
	return 0;
}
