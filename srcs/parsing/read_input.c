/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: link <link@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:48:40 by Link           #+#    #+#             */
/*   Updated: 2023/10/18 15:14:42 by link             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

/**
 * @brief Verify that the line contains only digits
 * @param line The line to verify
 * @return 0 if the line contains only digits, 1 otherwise
*/
static int verify_numbers(char *line);

void parse_file(t_lem_in *lem_in) {
	char	*line;
	int		status = ANTS;
	int		cmd = NONE;

	// ft_printf("yoo\n");
	while ((line = get_next_line(0)) != NULL) {
		// ft_printf("inside\n");
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
			lem_in->nb_ants = process_ants(lem_in, line, &status);
		else if (status == ROOMS)
			process_rooms(lem_in, line, &cmd, &status);
		else if (status == LINKS)
			process_links(lem_in, line);
	}
	// ft_printf("yay??\n");
	if (status != LINKS)
		bugs(lem_in, ERR_NO_LINKS);
	// ft_printf("yay\n");
	print_lemin(lem_in);
}

void process_rooms(t_lem_in *lemin, char *line, int *cmd, int *status) {

	if (ft_strchr(line, '-') != NULL) {
		if (*cmd != NONE)
			bugs(lemin, ERR_CMD_LINK);
		*status = LINKS;
		return;
	}
	
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
	char coord2[16];
	while (*mid_coords != '\0') {
		coord2[i] = *(mid_coords + i);
		i++;
	}
	coord2[i] = '\0';
	if (verify_numbers(coord2) || !ft_strlen(coord2))
		bugs(lemin, ERR_ROOM_SYNTAX);
	
	// Add the room to the structure
	int ret = add_room(lemin->rooms, name, *cmd & START, *cmd & END, ft_atoi(coord), ft_atoi(coord2));
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

int process_ants(t_lem_in *lemin, char *line, int *status) {
	if (verify_numbers(line))
		bugs(lemin, ERR_VALUE_ANTS);
	*status = ROOMS;
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
