/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:18:09 by Link           #+#    #+#             */
/*   Updated: 2023/11/09 10:50:37 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/processing.h"

extern t_lem_in *lem_in;

void throw_ants() {
	for (int i = 0 ; i < lem_in->graph->nb_edges; i++)
	{
		int flow = lem_in->graph->edges[i]->flow;
		if (flow)
		ft_printf("%d\n", flow);
	}
}

