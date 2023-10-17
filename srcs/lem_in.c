/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:04:24 by Link           #+#    #+#             */
/*   Updated: 2023/10/17 11:31:38 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#include "../includes/init.h"

int	main(int argc, char **argv)
{
	t_lem_in	lem_in;

	if (argc != 1)
	{
		ft_putendl_fd("Usage: ./lem-in < map_file", 1);
		return (1);
	}

	// Init
	lem_in.rooms = init();
	// Parse file & store data
	ft_printf("Parsing file...\n");
	parse_file();

	// Determine Pentries and Pexits

	// Check if Pentries and Pexits are connected OR Entry connected to Exit

	// Find all paths to Pexits to keep the min(Pentries, Pexits) shortest and parallels paths

	// Check for conflicts (warning infinite loop)

	// Throw ants on the paths (but be aware for how many of them, size of the path etc.)

	// Tini
	tini(lem_in.rooms);
	return (0);
}
