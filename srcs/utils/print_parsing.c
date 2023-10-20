/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Link <Link@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:52:15 by link              #+#    #+#             */
/*   Updated: 2023/10/20 15:04:31 by Link          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void print_lemin(t_lem_in *lemin) {
	ft_printf("%d\n", lemin->nb_ants);
	print_rooms(*(lemin->rooms));
	print_links(*(lemin->rooms));
	ft_printf("\net la on met les tours qui passent\n");
}

void print_rooms(t_room *room) {
	if (room == NULL)
		return ;
	if (room->is_start)
		ft_printf("##start\n");
	if (room->is_end)
		ft_printf("##end\n");
	ft_printf("%s %d %d [", room->name, room->x_coord, room->y_coord);

	int	*distances = room->distances_to_ends;
	while (distances && *distances)
	{
		ft_printf("%d,", *distances);
		distances++;
	}

	ft_printf("]\n");
	print_rooms(room->left);
	print_rooms(room->right);
}

void print_links(t_room *room)
{
	if (room == NULL)
		return ;
	for (int i = 0 ; i < room->nb_linked ; i++)
	{
		ft_printf("%s-%s\n", room->name, room->linked_rooms[i]->name);
	}
	print_links(room->left);
	print_links(room->right);
}
