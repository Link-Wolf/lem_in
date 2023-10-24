/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:18:09 by Link           #+#    #+#             */
/*   Updated: 2023/10/24 13:01:42 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/processing.h"

// static int nb_greater_paths(int *dist_by_path, int nb_paths, int dist);
static void print_them_all(t_lem_in *lemin, int *ants_by_path);
static int tab_sum_min(int *tab1, int *tab2, int size);

void throw_ants(t_lem_in *lemin) {
	int nb_paths = lemin->nb_def_paths;
	ft_printf("nb_paths: %d\n", nb_paths);
	if (!nb_paths)
		bugs(lemin, ERR_NO_SOLUTION);
	int *dist_by_path = (int *)malloc(sizeof(int) * nb_paths);
	int *ants_by_path = (int *)ft_calloc(nb_paths, sizeof(int));
	if (!dist_by_path || !ants_by_path) {
		free(dist_by_path);
		free(ants_by_path);
		bugs(lemin, ERR_ALLOCATION);
	}


	for (int i = 0; i < nb_paths; i++)
	{

		ft_printf("path %d: %d\n", i, lemin->def_paths[i]->depth);
		dist_by_path[i] = lemin->def_paths[i]->depth;
	}

	while (lemin->nb_ants) {
		int min = tab_sum_min(dist_by_path, ants_by_path, nb_paths);
		//ft_printf("min: %d\n", min);
		for (int i = 0; i < nb_paths; i++) {
			if (dist_by_path[i] + ants_by_path[i] <= min) {
				ants_by_path[i]++;
				//ft_printf("moi mettre fourmi dans path %d, reste %d fourmis\n", i, lemin->nb_ants - 1);
				lemin->nb_ants--;
				if (!lemin->nb_ants)
					break ;
			}
		}
	}
	free(dist_by_path);
	print_them_all(lemin, ants_by_path);
}

// static int nb_greater_paths(int *dist_by_path, int nb_paths, int dist) {
// 	int count = 0;

// 	for (int i = 0; i < nb_paths; i++) {
// 		if (dist_by_path[i] > dist)
// 			count++;
// 	}
// 	return (count);
// }

static void print_them_all(t_lem_in *lemin, int *ants_by_path) {
	for (int i = 0; i < lemin->nb_def_paths; i++) {
		ft_printf("ants_by_path[%d]: %d\n", i, ants_by_path[i]);
	}
}

static int tab_sum_min(int *tab1, int *tab2, int size) {
	int	res;
	int i = 0;

	res = 2147483647;
	while (size--)
	{
		if (res > tab1[i] + tab2[i])
			res = tab1[i] + tab2[i];
		i++;
	}
	return (res);
}
