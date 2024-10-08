/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:48:40 by Link           #+#    #+#             */
/*   Updated: 2023/11/22 13:27:52 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

extern t_lem_in *lem_in;

/**
 * @brief Verify that the line contains only digits
 * @param line The line to verify
 * @param minus 1 if the line can contain a negative value, 0 otherwise
 * @return 0 if the line contains only digits, 1 otherwise
*/
static int verify_numbers(char *line, int minus);

void parse_file(t_mode mode) {
	char	*line = NULL;
	int		status = ANTS;
	int		cmd = NONE;

	// NOTE: clever use of , operator to free and allocate line in one scoop
	//		and keep the functionnality
	while ((free(line), line = get_next_line(0)) != NULL) {
		// Verify that the line following a command is a room
		if ((cmd == START || cmd == END) && (status != ROOMS || line[0] == '#'))
			bugs(ERR_CMD_ROOM);

		// Case of commands and comments lines
		if (line[0] == '#')
		{
			if (line[1] && line[1] == '#')
				process_cmd(line, &cmd, mode);
			else if (lem_in->verbose)
				ft_putstr_fd(line, 1);
			continue;
		}

		// Case of ants, rooms and links lines
		if (status == ANTS) {
			lem_in->nb_ants = process_ants(line, &status, mode);
			if (mode == DEFAULT)
			{
				if (lem_in->verbose)
					ft_putstr_fd("#------ ANT NUMBER ------\n", 1);
				ft_putnbr_fd(lem_in->nb_ants, 1);
				ft_putchar_fd('\n', 1);
			}
		}
		else if (status == ROOMS)
			process_rooms(line, &cmd, &status, mode);
		if (status == LINKS)
			process_links(line, mode);
	}
	if (status != LINKS)
		bugs(ERR_NO_LINKS);
	// print_lem_in(lem_in);
}

void process_rooms(char *line, int *cmd, int *status, t_mode mode) {

	if (ft_strchr(line, ' ') == NULL) {
		if (*cmd != NONE)
			bugs(ERR_CMD_LINK);
		*status = LINKS;
		if (!lem_in->start || !lem_in->end)
			bugs(ERR_NO_START_END);
		if (lem_in->verbose && mode == DEFAULT)
			ft_putstr_fd("\n#--- LINKS DEFINITION ---\n", 1);
		return;
	}

	// Verify that the line contains a space after the name
	char *find = ft_strchr(line, ' ') + 1;
	if (find == NULL + 1 || find == line || find == line + 1)
		bugs(ERR_ROOM_SYNTAX);

	// Get the room name
	int i = 0;
	char name[NAME_SIZE + 1];

	while (*find != *line && i < NAME_SIZE && *(line + i) && *(line + i) != ' ') {
		name[i] = *(line + i);
		i++;
	}
	name[i] = '\0';

	// Get the room first coordinate
	i = 0;
	char coord[16];
	char *mid_coords = ft_strchr(find + 1, ' ');

	if (mid_coords == NULL || mid_coords == find)
		bugs(ERR_ROOM_SYNTAX);
	while (*(find + i) != ' ') {
		coord[i] = *(find + i);
		i++;
	}
	coord[i] = '\0';

	if (verify_numbers(coord, 1) || !ft_strlen(coord))
		bugs(ERR_ROOM_SYNTAX);

	// Get the room second coordinate
	i = 0;
	char coord2[16];
	mid_coords++;
	while (*mid_coords != '\0' && *(mid_coords + i)) {
		coord2[i] = *(mid_coords + i);
		i++;
	}
	coord2[i] = '\0';
	if (verify_numbers(coord2, 1) || !ft_strlen(coord2))
		bugs(ERR_ROOM_SYNTAX);


	//TODO : delete
	lem_in->nb_rooms++;


	// Add the room to the structure
	int ret = add_room(
		name,
		*cmd & START,
		*cmd & END,
		ft_atoi(coord),
		ft_atoi(coord2)
		,mode
	);
	*cmd = NONE;
	if (ret > 0)
		bugs(ret);
}

void process_links(char *line, t_mode mode) {
	// Verify that the line contains a dash
	char *find = ft_strchr(line, '-') + 1;
	if (find == NULL + 1 || find == line || find == line + 1)
		bugs(ERR_LINK_SYNTAX);

	// Get the first room name
	int i = 0;
	char name[NAME_SIZE + 1];

	while (i < NAME_SIZE && *(line + i) && *(line + i) != '-') {
		name[i] = *(line + i);
		i++;
	}
	name[i] = '\0';

	// Get the second room name
	i++;
	int j = 0;
	char name2[NAME_SIZE + 1];
	while (line[i] && j < NAME_SIZE && *(line + i) && *(line + i) != '\n') {
		name2[j] = *(line + i);
		i++;
		j++;
	}
	name2[j] = '\0';


	//TODO: delete
	lem_in->nb_links++;


	// Add the link to the structure
	int ret = add_link(lem_in->rooms, name, name2, mode);
	if (ret > 0)
		bugs(ret);
}

void process_cmd(char *line, int *cmd, t_mode mode) {
	(void) mode;
	if (ft_strcmp(line, "##start\n") == 0)
		*cmd = START;
	else if (ft_strcmp(line, "##end\n") == 0)
		*cmd = END;
}

int process_ants(char *line, int *status, t_mode mode) {
	if (verify_numbers(line, 0))
		bugs(ERR_VALUE_ANTS);
	*status = ROOMS;
	if (lem_in->verbose && mode == DEFAULT)
		ft_putstr_fd("\n#--- ROOMS DEFINITION ---\n", 1);
	return (ft_atoi(line));
}

static int verify_numbers(char *line, int minus) {
	int i = 0;
	if (minus == 1 && line[i] == '-')
		i++;
	while (line[i])	{
		if (!ft_isdigit(line[i]) && line[i] != '\n')
			return 1;
		i++;
	}
	return 0;
}
