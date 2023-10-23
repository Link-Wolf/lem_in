/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conflicts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:49:45 by Link           #+#    #+#             */
/*   Updated: 2023/10/23 17:05:033 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/processing.h"

static int check_conflicts(t_cache *cache, int *current_state, t_lem_in *lemin);
static int	is_in_cache(t_cache *cache, int *state, t_lem_in *lemin);
static long long is_conflicts(int *current_state, t_lem_in *lemin);
static t_pathes *get_parent_on_n_generations(t_pathes *path, int n);

void	manage_conflicts(t_lem_in *lemin) {
	int		nb_psexit = lemin->end->nb_linked;
	int		nb_pstart = lemin->start->nb_linked;
	int		nb_def_paths = ft_min(nb_psexit, nb_pstart);
	int		*fastests = ft_calloc(nb_def_paths, sizeof (int));
	if (!fastests) {
		free(fastests);
		bugs(lemin, ERR_ALLOCATION);
	}

	for (int i = 0 ; i < nb_def_paths ; i++)
		fastests[i] = -1;

	// fill up fastest with the indexes of the nb_def_paths smallests pathes
	// XXX: DO IT FUCKING GOOD

	t_cache	cache;
	cache.nb_data = 0;
	cache.max_data = 8;
	cache.data = ft_calloc(cache.max_data + 1, sizeof (int *));
	if (!cache.data) {
		free(fastests);
		bugs(lemin, ERR_ALLOCATION);
	}
	int ret = check_conflicts(&cache, fastests, lemin);
	free(fastests);
	for (int i = 0; i < cache.nb_data ; i++)
		free(cache.data[i]);
	free(cache.data);
	if (ret == -1)
		bugs(lemin, ERR_ALLOCATION);
	if (ret == 0)
		bugs(lemin, ERR_NO_SOLUTION);
	//for each path in fastests, check if it's in the other paths
	//to do so, big recursive boi
	// :D
}

static int check_conflicts(t_cache *cache, int *current_state, t_lem_in *lemin)
{
	// check if current state is in cache
		// if yes : return
	if (is_in_cache(cache, current_state, lemin))
		return (0);
	// check if conflicts in current state
		// if not conflict : return mais content
	long	conflicts = is_conflicts(current_state, lemin);
	if (!conflicts)
	{
		int	nb_pathes = 0;
		for (int i = 0; i < ft_min(lemin->end->nb_linked, lemin->start->nb_linked); i++)
		{
			if (current_state[i] != -1)
				nb_pathes++;
		}
		lemin->nb_def_paths = nb_pathes;
		lemin->def_paths = malloc(sizeof(t_pathes *) * nb_pathes);
		for (int i = 0, j = 0; i < ft_min(lemin->end->nb_linked, lemin->start->nb_linked); i++)
		{
			if (current_state[i] != -1)
				lemin->def_paths[j++] = lemin->good_pathes[i][current_state[i]];
		}
		return (1); //YAYYYYYYYY !!!!! :D :D :D :D :D :D :D :D :D :D :D :D :D :D :D :D :D
	}
	// generate all fixes for the conflict that are not already tested
		// if no fixes -> return
	if (cache->nb_data >= cache->max_data)
	{
		cache->max_data *= 2;
		int **tmp = malloc((cache->max_data + 1) * sizeof (int *));
		if (!tmp)
			return -1;
		ft_memcpy(tmp, cache->data, cache->nb_data * sizeof (int *));
		free(cache->data);
		cache->data = tmp;
	}
	cache->data[cache->nb_data++] = ft_memdup(current_state, ft_min(lemin->end->nb_linked, lemin->start->nb_linked) * sizeof (int));
	if (!cache->data[cache->nb_data - 1])
		return (-1);
	int	room1 = conflicts & INT_MAX;
	int	room2 = conflicts >> 32;
	int i = current_state[room1];
	while (lemin->good_pathes[room1][current_state[room1]]->depth >= lemin->good_pathes[room1][i]->depth)
	{
		int j = current_state[room2];
		while (lemin->good_pathes[room2][current_state[room2]]->depth >= lemin->good_pathes[room2][j]->depth)
		{
			// call check_conflicts on all children	=
			int *tmp = ft_memdup(current_state, ft_min(lemin->end->nb_linked, lemin->start->nb_linked) * sizeof (int));
			if (!tmp)
				return (-1);
			tmp[room1] = i;
			tmp[room2] = j;
			int ret = check_conflicts(cache, tmp, lemin);
			free(tmp);
			if (ret)
				return (ret);
			j++;
		}
		i++;
	}
	return (0);
}


static int	is_in_cache(t_cache *cache, int *state, t_lem_in *lemin)
{
	for (int i = 0; i < cache->nb_data ; i++)
	{
		if (
			!ft_memcmp(cache->data[i],
			state,
			ft_min(lemin->end->nb_linked, lemin->start->nb_linked)))
			return (1);
	}
	return (0);
}

static long long is_conflicts(int *current_state, t_lem_in *lemin)
{
	for (int i = 0 ; i < ft_min(lemin->end->nb_linked, lemin->start->nb_linked) ; i++) {
		for (int j = i + 1 ; j < ft_min(lemin->end->nb_linked, lemin->start->nb_linked) ; j++) {
			if (current_state[i] != -1 && current_state[j] != -1)
			{
				for (int k = 0 ; k < lemin->good_pathes[i][current_state[i]]->depth ; k++) {
					for (int l = 0 ; l < lemin->good_pathes[j][current_state[j]]->depth ; l++) {
						if (get_parent_on_n_generations(lemin->good_pathes[j][current_state[j]], l) == get_parent_on_n_generations(lemin->good_pathes[i][current_state[i]], k))
							return (i + j * INT_MAX);
					}
				}
			}
		}

	}
	return (0);
}

static t_pathes *get_parent_on_n_generations(t_pathes *path, int n)
{
	if (n == 0 || !path)
		return (path);
	return (get_parent_on_n_generations(path->parent, n - 1));
}
