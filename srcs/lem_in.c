/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:04:24 by Link           #+#    #+#             */
/*   Updated: 2023/10/18 11:05:42 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#include "../includes/init.h"
#include "../includes/parsing.h"

int	main(int argc, char **argv)
{
	t_lem_in	lem_in;

	if (argc != 1)
	{
		ft_putendl_fd("Usage: ./lem-in < map_file", 1);
		return (1);
	}
	(void) argv;

	// Init
	lem_in.rooms = init();
	// Parse file & store data
	ft_printf("Parsing file...\n");
	parse_file(&lem_in);

	// Determine Pentries and Pexits

	// Check if Pentries and Pexits are connected OR Entry connected to Exit

	// Find all paths to Pexits to keep the min(Pentries, Pexits) shortest and parallels paths

	// Check for conflicts (warning infinite loop)

	// Throw ants on the paths (but be aware for how many of them, size of the path etc.)

	// Tini
	tini(lem_in.rooms);
	return (0);
}
