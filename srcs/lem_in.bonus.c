/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:04:24 by Link           #+#    #+#             */
/*   Updated: 2023/11/14 18:01:13 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_lem_in	*lem_in = NULL;

int	main(int argc, char **argv)
{
	init();

	int flags = 0;
	if (argc >= 2 && (!ft_strcmp(argv[1], "-h") || !ft_strcmp(argv[1], "--help")))
	{
		ft_putendl_fd("Usage:\n\t./visualiser [ -h | --help ] [ -d | --debugger ] < map_file\n\n\tNOTE: map_file can be replaced by the map generator as follow:\n\t\t./generator_linux [ --flow-one | --flow-ten | --flow-thousand | --big | --big-superposition ] | ./visualiser [ -h | --help ] [ -d | --debugger ]\n\tNOTE2: without the -d (--debugger) option, please only use maps contained under /bonus_maps", 1);
		return (0);
	}
	for (int i = 1; i < argc; i++)
	{
		if (!ft_strcmp(argv[i], "-d") || !ft_strcmp(argv[i], "--debugger"))
			flags |= DEBUGGER;
		else
			bugs(ERR_USAGE_BONUS);
	}
	lem_in->verbose = flags & VERBOSE;
	lem_in->has_visualiser = flags & VISUALISER;

	// Parse file & store data
	parse_file(SILENT);
	resolve();

	if (flags & DEBUGGER)
	{
		evaluate_coords();
		debug();
	}
	else
	{
		visualize(SILENT);
	}

	// Tini, propers frees and exit
	tini();

	return (0);
}
