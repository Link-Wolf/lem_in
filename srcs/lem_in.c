/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:04:24 by Link           #+#    #+#             */
/*   Updated: 2023/10/23 18:00:44 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	main(int argc, char **argv)
{
	(void) argv;
	if (argc != 1)
	{
		ft_putendl_fd("Usage: ./lem-in < map_file", 1);
		return (1);
	}

	t_lem_in	lem_in;
	init(&lem_in);

	// Parse file & store data
	parse_file(&lem_in);

	// Check for trivial cases to avoid useless computations
	// check_for_trivials(&lem_in);

	// Evaluate distances between each room and each Pend (aka a room connected to the end)
	evaluate_distances(&lem_in);

	// Find all paths to Pends to keep the min(Pentries, Pends) shortest and parallels paths
	create_pathes(&lem_in);

	// Sort all the stored paths depending on their distance between their Pentry and Pend
	sort_pathes(&lem_in);

	// Check for conflicts
	manage_conflicts(&lem_in);

	// Throw ants on the paths
	throw_ants(&lem_in);

	// Tini, propers frees and exit
	tini(&lem_in);

	return (0);
}
