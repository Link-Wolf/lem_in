/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:18:34 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/30 10:20:00 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	init(t_lem_in *lem_in)
{
	lem_in->end = NULL;
	lem_in->start = NULL;
	lem_in->pathes = NULL;
	lem_in->def_paths = NULL;
	lem_in->good_pathes = NULL;
	lem_in->nb_pathes_leaves = NULL;
	lem_in->max_pathes_leaves = NULL;
	lem_in->nb_ants = 0;
	lem_in->verbose = 0;
	lem_in->nb_def_paths = 0;
	lem_in->nb_rooms = 0;
	lem_in-> nb_links = 0;
	lem_in->rooms = ft_calloc(1, sizeof (t_room *));
	lem_in->visualiser = ft_calloc(1, sizeof (t_visualiser));
	lem_in->visualiser->room_line_size = NULL;
	if (!lem_in->rooms || !lem_in->visualiser)
		bugs(lem_in, ERR_ALLOCATION);
}

void	tini(t_lem_in *lem_in)
{
	if (lem_in->pathes)
	{
		for (int i = 0; i < lem_in->end->nb_linked ; i++)
		{
			delete_pathes(lem_in->pathes[i]);
			free(lem_in->good_pathes[i]);
		}
	}
	free(lem_in->good_pathes);
	free(lem_in->nb_pathes_leaves);
	free(lem_in->max_pathes_leaves);
	delete_room(*(lem_in->rooms));
	free(lem_in->rooms);
	free(lem_in->pathes);
	free(lem_in->def_paths);
	free(lem_in->visualiser->room_line_size);
	free(lem_in->visualiser);
}
