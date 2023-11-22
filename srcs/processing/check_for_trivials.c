/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_trivials.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:18:02 by iCARUS            #+#    #+#             */
/*   Updated: 2023/11/22 14:06:23 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/processing.h"

extern t_lem_in *lem_in;

void	check_for_trivials()
{
	//check if start and end are directly linked
	for (int i = 0; i < lem_in->start->nb_linked; i++)
	{
		if (lem_in->start->linked_rooms[i] == lem_in->end)
		{
			//throw all ants in the end room
			ft_printf("L1-%s", lem_in->end->name);
			for (int j = 1; j < lem_in->nb_ants - 1; j++)
				ft_printf(" L%d-%s", j + 1, lem_in->end->name);
			if (lem_in->nb_ants > 1)
				ft_printf(" L%d-%s\n", lem_in->nb_ants, lem_in->end->name);
			else
				ft_printf("\n");
			bugs(OK);
		}
	}
	return;
}
