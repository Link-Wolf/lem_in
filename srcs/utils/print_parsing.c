/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:52:15 by link              #+#    #+#             */
/*   Updated: 2023/11/08 16:06:10 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

extern t_lem_in *lem_in;

void print_lemin() {
	ft_printf("%d\n", lem_in->nb_ants);
	print_rooms(*(lem_in->rooms));
	print_links(*(lem_in->rooms));
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
