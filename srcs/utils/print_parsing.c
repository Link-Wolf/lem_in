/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: link <link@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:52:15 by link              #+#    #+#             */
/*   Updated: 2023/10/18 16:53:39 by link             ###   ########.fr       */
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
	if (room->is_entry)
		ft_printf("##start\n");
	if (room->is_exit)
		ft_printf("##end\n");
	ft_printf("%s %d %d\n", room->name, room->x_coord, room->y_coord);
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