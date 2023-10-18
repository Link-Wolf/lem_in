/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:18:34 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/18 11:13:18 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/init.h"

// TODO: use t_lem_in instead of t_room

t_room	**init(void)
{
	return (ft_calloc(1, sizeof (t_room *)));
}

void	tini(t_lem_in *rooms)
{
	// TODO: free all rooms via tree parcouring
	free(rooms);
}
