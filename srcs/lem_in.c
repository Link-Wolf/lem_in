/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:04:24 by Link           #+#    #+#             */
/*   Updated: 2023/11/14 18:02:01 by iCARUS           ###   ########.fr       */
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
		ft_putendl_fd("Usage:\n\t./lem-in [ -h | --help ] [ -v | --verbose ] < map_file\n\n\tNOTE: map_file can be replaced by the map generator as follow:\n\t\t./generator_linux [ --flow-one | --flow-ten | --flow-thousand | --big | --big-superposition ] | ./lem-in [ -h | --help ] [ -v | --verbose ]", 1);
		return (0);
	}
	for (int i = 1; i < argc; i++)
	{
		if (!ft_strcmp(argv[i], "-v") || !ft_strcmp(argv[i], "--verbose"))
			flags |= VERBOSE;
		else
			bugs(ERR_USAGE);
	}
	lem_in->verbose = flags & VERBOSE;

	// Parse file & store data
	parse_file(DEFAULT);

	resolve();


	// Throw ants on the paths
	throw_ants(DEFAULT);

	// Tini, propers frees and exit
	tini();

	return (0);
}
