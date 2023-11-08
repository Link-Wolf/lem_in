/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:18:09 by Link           #+#    #+#             */
/*   Updated: 2023/11/08 16:03:47 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/processing.h"

// static int nb_greater_paths(int *dist_by_path, int nb_paths, int dist);
// static void print_them_all(t_lem_in *lem_in, int *ants_by_path);
// static int tab_sum_min(int *tab1, int *tab2, int size);
// static t_ant search_path_for_ant(t_lem_in *lem_in, int *ants_by_path, int *occupied, int id);

void throw_ants() {
	ft_printf("throw_ants\n");

	// int nb_paths = lem_in->nb_def_paths;
	// if (!nb_paths)
	// 	bugs(lem_in, ERR_NO_SOLUTION);
	// int *dist_by_path = (int *)malloc(sizeof(int) * nb_paths);
	// int *ants_by_path = (int *)ft_calloc(nb_paths, sizeof(int));
	// if (!dist_by_path || !ants_by_path) {
	// 	free(dist_by_path);
	// 	free(ants_by_path);
	// 	bugs(lem_in, ERR_ALLOCATION);
	// }

	// ft_printf("nb_paths: %d\n", nb_paths);
	// for (int i = 0; i < nb_paths; i++) {
	// 	ft_printf("path %d:  %p\n", i, lem_in->def_paths[i]);
	// 	dist_by_path[i] = lem_in->def_paths[i]->depth;
	// }

	// int nb_ants = lem_in->nb_ants;
	// while (nb_ants) {
	// 	int min = tab_sum_min(dist_by_path, ants_by_path, nb_paths);
	// 	//ft_printf("min: %d\n", min);aa
	// 	for (int i = 0; i < nb_paths; i++) {
	// 		if (dist_by_path[i] + ants_by_path[i] <= min) {
	// 			ants_by_path[i]++;
	// 			//ft_printf("moi mettre fourmi dans path %d, reste %d fourmis\n", i, lem_in->nb_ants - 1);
	// 			nb_ants--;
	// 			if (!nb_ants)
	// 				break ;
	// 		}
	// 	}
	// }
	// free(dist_by_path);
	// print_them_all(lem_in, ants_by_path);
	// free(ants_by_path);
}

// static int nb_greater_paths(int *dist_by_path, int nb_paths, int dist) {
// 	int count = 0;

// 	for (int i = 0; i < nb_paths; i++) {
// 		if (dist_by_path[i] > dist)
// 			count++;
// 	}
// 	return (count);
// }

// static void print_them_all(t_lem_in *lem_in, int *ants_by_path) {

// 	t_ant *ants = (t_ant *)malloc(sizeof(t_ant) * lem_in->nb_ants);
// 	if (!ants) {
// 		free(ants_by_path);
// 		bugs(lem_in, ERR_ALLOCATION);
// 	}
// 	int *occupied = ft_calloc(lem_in->nb_def_paths, sizeof(char *));
// 	if (!occupied) {
// 		free(ants_by_path);
// 		free(ants);
// 		bugs(lem_in, ERR_ALLOCATION);
// 	}

// 	for (int i = 0; i < lem_in->nb_ants; i++) {
// 		ants[i] = search_path_for_ant(lem_in, ants_by_path, occupied, i + 1);
// 	}

// 	int nb_arrived = 0;
// 	int nb_turns = 0;

// 	// ft_printf("entry %s, exit %s\n", lem_in->start->name, lem_in->end->name);

// 	// for (int i =0; i <lem_in->end->nb_linked; i++)
// 	// 	ft_printf("end linked room %s\n", lem_in->end->linked_rooms[i]->name);

// 	// for (int i = 0; i < lem_in->start->nb_linked; i++)
// 	// 	ft_printf("start linked room %s\n", lem_in->start->linked_rooms[i]->name);

// 	while (nb_arrived < lem_in->nb_ants) {
// 		for (int i = 0; i < lem_in->nb_ants; i++) {
// 			if (ants[i].wait_turns) {
// 				ants[i].wait_turns--;
// 				continue ;
// 			}
// 			if (ants[i].where_to_go) {
// 					ft_printf("L%d-%s ", ants[i].id, ants[i].where_to_go->room->name);
// 					ants[i].where_to_go = ants[i].where_to_go->parent;
// 			}
// 			else if (!ants[i].is_arrived) {
// 				ft_printf("L%d-%s ", ants[i].id, lem_in->end->name);
// 				ants[i].is_arrived = 1;
// 				nb_arrived++;
// 			}
// 		}
// 		// for reset
// 		ft_printf("\n");
// 		nb_turns++;
// 	}
// 	if (lem_in->verbose)
// 		ft_printf("\n# > All ants found their way to the exit in %d turns !\n# > Wasn’t that ant-ertaining? (⁠｡⁠◕⁠‿⁠◕⁠｡⁠)\n", nb_turns);
// 	free(ants);
// 	free(occupied);
// }

// static t_ant search_path_for_ant(t_lem_in *lem_in, int *ants_by_path, int *occupied, int id)
// {
// 	t_ant ant;

// 	ant.id = id;
// 	ant.is_arrived = 0;

// 	for (int i = 0; i < lem_in->nb_def_paths; i++) {
// 		if (ants_by_path[i] > 0)
// 		{
// 			ants_by_path[i]--;
// 			ant.wait_turns = occupied[i]++;
// 			ant.where_to_go = lem_in->def_paths[i];
// 			break;
// 		}
// 	}
// 	return (ant);
// }

// static int tab_sum_min(int *tab1, int *tab2, int size) {
// 	int	res;
// 	int i = 0;

// 	res = 2147483647;
// 	while (size--)
// 	{
// 		if (res > tab1[i] + tab2[i])
// 			res = tab1[i] + tab2[i];
// 		i++;
// 	}
// 	return (res);
// }
