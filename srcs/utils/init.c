/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:18:34 by iCARUS            #+#    #+#             */
/*   Updated: 2023/11/01 11:00:28 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	init(t_lem_in *lem_in)
{
	lem_in->end = NULL;
	lem_in->start = NULL;
	lem_in->nb_ants = 0;
	lem_in->verbose = 0;
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
	delete_room(*(lem_in->rooms));
	free(lem_in->rooms);
	free(lem_in->visualiser->room_line_size);
	free(lem_in->visualiser);
}
