/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:04:24 by Link           #+#    #+#             */
/*   Updated: 2023/11/11 15:21:35 by iCARUS           ###   ########.fr       */
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
