/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Link <Link@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:18:34 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/20 17:24:36 by Link          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

// TODO: use t_lem_in instead of t_room

void	init(t_lem_in *lem_in)
{
	lem_in->rooms = ft_calloc(1, sizeof (t_room *));
	lem_in->end = NULL;
	lem_in->start = NULL;
	lem_in->pathes = NULL;
	lem_in->nb_ants = 0;
}

void	tini(t_lem_in *lem_in)
{
	delete_room(*(lem_in->rooms));
	if (lem_in->pathes)
		delete_pathes(*(lem_in->pathes));
	free(lem_in->rooms);
	free(lem_in->pathes);
}
