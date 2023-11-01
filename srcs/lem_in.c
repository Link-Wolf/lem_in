/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:04:24 by Link           #+#    #+#             */
/*   Updated: 2023/11/01 11:15:28 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	main(int argc, char **argv)
{
	t_lem_in	lem_in;
	init(&lem_in);

	int flags = 0;
	for (int i = 1; i < argc; i++)
	{
		if (!ft_strcmp(argv[i], "-v") || !ft_strcmp(argv[i], "--verbose"))
			flags |= VERBOSE;
		else if (!ft_strcmp(argv[i], "-b") || !ft_strcmp(argv[i], "--bonus"))
			flags |= VISUALIZER;
		else
			bugs(&lem_in, ERR_USAGE);
	}
	lem_in.verbose = flags & VERBOSE;
	lem_in.has_visualizer = flags & VISUALIZER;

	// Parse file & store data
	parse_file(&lem_in);
	print_matrix(lem_in.matrix);

	// Check for trivial cases to avoid useless computations
	// check_for_trivials(&lem_in);

	// Evaluate distances between each room and each Pend (aka a room connected to the end)

	if (lem_in.has_visualizer)
	{
		evaluate_distances(&lem_in);
		visualise(&lem_in);
	}

	// Throw ants on the paths
	//throw_ants(&lem_in);

	// Tini, propers frees and exit
	tini(&lem_in);

	return (0);
}
