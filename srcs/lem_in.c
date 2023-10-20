/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:04:24 by Link           #+#    #+#             */
/*   Updated: 2023/10/20 15:47:24 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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
	init(&lem_in);
	// Parse file & store data
	parse_file(&lem_in);

	// Determine Pentries and Pends

	// Check if Pentries and Pends are connected OR start connected to end
	if (check_for_trivials(&lem_in) == 0)
		evaluate_distances(&lem_in);

	// Find all paths to Pends to keep the min(Pentries, Pends) shortest and parallels paths

	// Check for conflicts (warning infinite loop)

	// Throw ants on the paths (but be aware for how many of them, size of the path etc.)
	throw_ants(&lem_in);

	// Tini
	tini(&lem_in);
	return (0);
}
