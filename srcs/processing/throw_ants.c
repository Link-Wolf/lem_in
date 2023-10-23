/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:18:09 by Link           #+#    #+#             */
/*   Updated: 2023/10/23 17:37:28 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/processing.h"

static int nb_greater_equal_paths(int *dist_by_path, int nb_paths, int dist);
static void print_them_all(t_lem_in *lemin, int *ants_by_path);

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
		dist_by_path[i] = lemin->def_paths[i]->depth;

	while (lemin->nb_ants) {
		for (int i = 0; i < nb_paths; i++) {
			if (dist_by_path[i] <= ((ft_tabmin(dist_by_path, nb_paths) + lemin->nb_ants) / nb_paths - nb_greater_equal_paths(dist_by_path, nb_paths, dist_by_path[i]))) {
				ants_by_path[i]++;
				lemin->nb_ants--;
			}
		}
	}
	free(dist_by_path);
	print_them_all(lemin, ants_by_path);
}

static int nb_greater_equal_paths(int *dist_by_path, int nb_paths, int dist) {
	int count = 0;

	for (int i = 0; i < nb_paths; i++) {
		if (dist_by_path[i] >= dist)
			count++;
	}
	return (count);
}

static void print_them_all(t_lem_in *lemin, int *ants_by_path) {
	(void)lemin;
	free(ants_by_path);
	ft_printf("\n\nprint_them_all\n");
}
