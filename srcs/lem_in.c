/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:04:24 by Link           #+#    #+#             */
/*   Updated: 2023/11/10 10:46:40 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_lem_in	*lem_in = NULL;

int	main(int argc, char **argv)
{
	init();

	int flags = 0;
	for (int i = 1; i < argc; i++)
	{
		if (!ft_strcmp(argv[i], "-v") || !ft_strcmp(argv[i], "--verbose"))
			flags |= VERBOSE;
		else if (!ft_strcmp(argv[i], "-b") || !ft_strcmp(argv[i], "--bonus"))
			flags |= VISUALIZER;
		else
			bugs(ERR_USAGE);
	}
	lem_in->verbose = flags & VERBOSE;
	lem_in->has_visualizer = flags & VISUALIZER;

	// Parse file & store data
	parse_file();

	resolve();


	// Throw ants on the paths
	throw_ants(DEFAULT);

	if (lem_in->has_visualizer)
	{
		evaluate_distances();
		visualise();
	}

	// Tini, propers frees and exit
	tini();

	return (0);
}
