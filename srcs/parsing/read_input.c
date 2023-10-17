/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Link <Link@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:48:40 by Link           #+#    #+#             */
/*   Updated: 2023/10/17 13:25:16 by Link          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void parse_file(void)
{
	char *line;
	int status = ANTS;
	int cmd = NONE;

	while ((line = get_next_line(0)) != NULL)
	{
		if (line[0] == '#')
		{
			if (line[1] && line[1] == '#') {
				process_cmd(line, &cmd);
			} else continue;
		}
		if (status == ANTS)
			process_ants(line);
		else if (status == ROOMS)
			process_rooms(line);
		else if (status == LINKS)
			process_links(line);
	}
}

void process_cmd(char *line, int *cmd)
{
	if (ft_strcmp(line, "##start") == 0) {
		// toggle start
	}
	else if (ft_strcmp(line, "##end") == 0)	{
		// toggle end
	}
}
