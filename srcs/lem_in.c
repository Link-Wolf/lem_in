/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Link <Link@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:04:24 by Link           #+#    #+#             */
/*   Updated: 2023/10/16 17:04:47 by Link          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int main(int argc, char **argv)
{
	// Check args
	if (argc != 1)
	{
		ft_putendl_fd("Usage: ./lem-in < map_file", 1);
		return (1);
	}

	// Init

	// Parse file & store data
	ft_printf("Parsing file...\n");
	// parse_file();

	// Determine Pentries and Pexits

	// Check if Pentries and Pexits are connected OR Entry connected to Exit

	// Find all paths to Pexits to keep the min(Pentries, Pexits) shortest and parallels paths

	// Check for conflicts (warning infinite loop)

	// Throw ants on the paths (but be aware for how many of them, size of the path etc.)

	// Tini

	return (0);
}