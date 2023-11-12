/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:04:24 by Link           #+#    #+#             */
/*   Updated: 2023/11/12 15:59:32 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_lem_in	*lem_in = NULL;

int	main(int argc, char **argv)
{
	init();

	int flags = 0;
	t_mode	mode = SILENT;
	for (int i = 1; i < argc; i++)
	{
		if (!ft_strcmp(argv[i], "-d") || !ft_strcmp(argv[i], "--debugger"))
			flags |= DEBUGGER;
		else if (!ft_strcmp(argv[i], "-v") || !ft_strcmp(argv[i], "--verbose"))
			flags |= VERBOSE;
		else
			bugs(ERR_USAGE_BONUS);
	}
	lem_in->verbose = flags & VERBOSE;
	lem_in->has_visualizer = flags & VISUALIZER;

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
		visualize(mode);
	}

	// Tini, propers frees and exit
	tini();

	return (0);
}
