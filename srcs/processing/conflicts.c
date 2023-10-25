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

static int check_conflicts(int *initial_state, t_lem_in *lemin);
static long long is_conflicts(int *current_state, t_lem_in *lemin);
static t_pathes *get_parent_on_n_generations(t_pathes *path, int n);
static t_state *create_state(int *initial_state, int state_size, t_lem_in *lem_in);
static void free_state(void *state);
static int	is_in_cache(t_list **cache, int *state);
void quick_sort(t_list* first, t_list* last, t_lem_in *lem_in);
int compare_state(t_state *s1, t_state *s2, t_lem_in *lem_in);
t_list* partition(t_list* first, t_list* last, t_lem_in *lem_in);
int	calculate_value(int *state, t_lem_in *lem_in);

void	manage_conflicts(t_lem_in *lemin) {
	int		nb_psexit = lemin->end->nb_linked;
	int		nb_pstart = lemin->start->nb_linked;
	int		nb_def_paths = ft_min(nb_psexit, nb_pstart);
	int		*fastests = ft_calloc(nb_def_paths, sizeof (int));
	int		*initial_state = ft_calloc(nb_psexit, sizeof (int));

	if (!fastests) {
		free(fastests);
		bugs(lemin, ERR_ALLOCATION);
	}

	for (int i = 0 ; i < nb_def_paths ; i++)
		fastests[i] = -1;
	for (int i = 0; i < nb_psexit ; i++)
	{
		initial_state[i] = -1;
		for (int j = 0 ; j < nb_def_paths; j++)
		{
			if (fastests[j] == -1 || (lemin->nb_pathes_leaves[i] && lemin->nb_pathes_leaves[fastests[j]] && lemin->good_pathes[i][0]->depth < lemin->good_pathes[fastests[j]][0]->depth))
			{
				for (int k = nb_def_paths - 2 ; k >= j ; k--)
				{
					fastests[k + 1] = fastests[k];
				}
				fastests[j] = i;
				break;
			}
		}
	}
	for (int i = 0; i < nb_def_paths; i++)
	{
		if (fastests[i] != -1 && lemin->nb_pathes_leaves[fastests[i]])
			initial_state[fastests[i]] = 0;
	}

	int ret = check_conflicts(initial_state, lemin);

	free(fastests);
	if (ret)
		bugs(lemin, ret);
}

static int check_conflicts(int *initial_state, t_lem_in *lemin)
{
	t_list	**cache = ft_calloc(1, sizeof (t_list *));
	t_list	**wait_list = ft_calloc(1, sizeof (t_list *));

	ft_lstadd_back(
		wait_list,
		ft_lstnew(
			create_state(initial_state, lemin->end->nb_linked * sizeof (int), lemin)));
	while (*wait_list)
	{
		t_state *current = ((t_state *) (*wait_list)->content);
		long long	conflicts = is_conflicts(current->state, lemin);

		// ft_printf("testing state: (%d) ", current->value);
		// for (int i = 0; i < lemin->end->nb_linked; i++)
		// 	ft_printf("%d ", current->state[i]);
		// ft_printf("\n");

		if (!conflicts)
		{
			int nb_pathes = 0;
			for (int i = 0; i < ft_min(lemin->end->nb_linked, lemin->start->nb_linked); i++)
			{
				if (current->state[i] != -1)
					nb_pathes++;
			}
			lemin->nb_def_paths = nb_pathes;
			lemin->def_paths = malloc(sizeof(t_pathes *) * nb_pathes);
			for (int i = 0, j = 0; i < ft_min(lemin->end->nb_linked, lemin->start->nb_linked); i++)
			{
				if (current->state[i] != -1)
				{
					lemin->def_paths[j++] = lemin->good_pathes[i][current->state[i]];
				}
			}
			ft_lstclear(cache, free_state);
			ft_lstclear(wait_list, free_state);
			free(cache);
			free(wait_list);
			return (OK);
		}

		// move current->state from wait_list to cache
		t_list *tmp = (*wait_list)->next;
		(*wait_list)->next = *cache;
		*cache = *wait_list;
		*wait_list = tmp;

		// generate all possible states from current->state that resolve conflicts
		int		conflicted_pathes[2] = {conflicts & INT_MAX, conflicts >> 32};
		t_list **new_states = ft_calloc(1, sizeof (t_list *));
		for (int i = 0; i < 2 ; i++)
		{
			for (int j = 0; j < lemin->end->nb_linked; j++)
			{
				int *new_state = ft_memdup(current->state, lemin->end->nb_linked * sizeof (int));
				// The conflicted path try to go to it nexts possible path, and to delete itself
				if (j == conflicted_pathes[i])
				{
					for (int k = -1; k < lemin->nb_pathes_leaves[j]; k++)
					{
						new_state[j] = k;
						if (is_in_cache(cache, new_state))
							continue;
						ft_lstadd_back(
							new_states,
							ft_lstnew(
								create_state(
									ft_memdup(
										new_state,
										sizeof (int) * lemin->end->nb_linked),
										lemin->end->nb_linked * sizeof (int),
									lemin
								)));
					}
				}
				// The other pathes try to go in the place of the conflicted path
				else if (lemin->nb_pathes_leaves[j] && conflicted_pathes[i] != -1 && current->state[j] == -1)
				{
					new_state[j] = 0;
					new_state[conflicted_pathes[i]] = -1;
					if (is_in_cache(cache, new_state))
					{
						free(new_state);
						continue;
					}
						ft_lstadd_back(
							new_states,
							ft_lstnew(
								create_state(
									ft_memdup(
										new_state,
										sizeof (int) * lemin->end->nb_linked),
										lemin->end->nb_linked * sizeof (int),
									lemin
								)));
				}
				free(new_state);
			}
		}

		ft_lstadd_back(wait_list, *new_states);
		free(new_states);
		quick_sort(*wait_list,ft_lstlast(*wait_list), lemin);
	}
	ft_lstclear(wait_list, free_state);
	ft_lstclear(cache, free_state);
	free(wait_list);
	free(cache);
	return (ERR_NO_SOLUTION);
}

t_list* partition(t_list* first, t_list* last, t_lem_in *lem_in)
{
    // Get first node of given linked list
    t_list* pivot = first;
    t_list* front = first;
    t_state *temp = 0;
    while (front != NULL && front != last) {
        if (compare_state(front->content, pivot->content, lem_in) > 0) {
            pivot = first;

            // Swapping  node values
            temp = first->content;
            first->content = front->content;
            front->content = temp;

            // Visiting the next node
            first = first->next;
        }

        // Visiting the next node
        front = front->next;
    }

    // Change last node value to current->state node
    temp = first->content;
    first->content = last->content;
    last->content = temp;
    return pivot;
}

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

// static int tab_sum_max(int *tab1, int *tab2, int size) {
// 	int	res;
// 	int i = 0;

// 	res = -2147483648;
// 	while (size--)
// 	{
// 		if (res < tab1[i] + tab2[i])
// 			res = tab1[i] + tab2[i];
// 		i++;
// 	}
// 	return (res);
// }


int	calculate_value(int *state, t_lem_in *lem_in)
{
	int nb_paths = 0;
	int	smallest_path = INT_MAX;
	for (int i = 0; i < ft_min(lem_in->end->nb_linked, lem_in->start->nb_linked); i++)
	{
		if (state[i] != -1)
		{
			nb_paths++;
			if (smallest_path > lem_in->good_pathes[i][state[i]]->depth)
				smallest_path = lem_in->good_pathes[i][state[i]]->depth;
		}
	}
	if (!nb_paths)
		return (INT_MAX);
	return (lem_in->nb_ants * smallest_path / nb_paths);

	// int nb_paths = 0;
	// int total_depth = 0;
	// for (int i = 0; i < ft_min(lem_in->end->nb_linked, lem_in->start->nb_linked); i++)
	// {
	// 	if (state[i] != -1)
	// 	{
	// 		nb_paths++;
	// 		total_depth += lem_in->good_pathes[i][state[i]]->depth;
	// 	}
	// }
	// return (total_depth / nb_paths);
}

// Performing quick sort in  the given linked list
void quick_sort(t_list* first, t_list* last, t_lem_in *lem_in)
{
    if (first == last) {
        return;
    }
    t_list* pivot = partition(first, last, lem_in);

    if (pivot != NULL && pivot->next != NULL) {
        quick_sort(pivot->next, last, lem_in);
    }

    if (pivot != NULL && first != pivot) {
        quick_sort(first, pivot, lem_in);
    }
}

int compare_state(t_state *s1, t_state *s2, t_lem_in *lem_in)
{
	(void)lem_in;
	return (s1->value - s2->value);
}

static t_state *create_state(int *initial_state, int state_size, t_lem_in *lem_in)
{
	t_state	*ret = ft_calloc(1, sizeof (t_state));

	if (!ret)
		return (NULL);
	ret->state = initial_state;
	ret->state_size = state_size;
	ret->value = calculate_value(ret->state, lem_in);
	return (ret);
}

static void free_state(void *state)
{
	free(((t_state *) state)->state);
	free(state);
}

static int	is_in_cache(t_list **cache, int *state)
{
	t_list *tmp = *cache;

	while (tmp)
	{
		if (!ft_memcmp(((t_state *)tmp->content)->state, state, ((t_state *)tmp->content)->state_size))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static long long is_conflicts(int *current_state, t_lem_in *lemin)
{
	// loop on all pair of state to check if there is a conflict
		// if one state or the other is -1, skip
		// for each pair, loop on all rooms of the pathes
			// if the rooms are the same, return the index of the pathes concatenated in a long long
	// if no conflict, return 0
	for (int i = 0; i < lemin->end->nb_linked; i++)
	{
		if (current_state[i] == -1)
			continue;
		for (long long j = i + 1; j < lemin->end->nb_linked; j++)
		{
			if (current_state[j] == -1)
				continue;
			if (
				lemin->nb_pathes_leaves[i] <= current_state[i]
					|| lemin->nb_pathes_leaves[j] <= current_state[j])
				return (i | (j << 32));
			for (int k = 0; k < lemin->good_pathes[i][current_state[i]]->depth; k++)
			{
				for (int l = 0; l < lemin->good_pathes[j][current_state[j]]->depth; l++)
				{
					t_pathes	*p1 = get_parent_on_n_generations(lemin->good_pathes[i][current_state[i]], k);
					t_pathes	*p2 = get_parent_on_n_generations(lemin->good_pathes[j][current_state[j]], l);
					if (!p1 || !p2)
						return (i | (j << 32));
					if (p1->room == p2->room)
						return (i | (j << 32));
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
