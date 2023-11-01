/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:29:34 by iCARUS            #+#    #+#             */
/*   Updated: 2023/11/01 16:53:41 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/processing.h"


static int	**tuples(int sum, int size , int *count);
static void	free_tuples(int** tuples, int count);
static void	generate_tuple(int* tuple, int index, int current_sum, int** tuples, int* tuples_count, int tuples_capacity, int size, int sum);
static int	min_lenght(t_lem_in *lem_in);
static int	max_lenght(t_lem_in *lem_in);
static int	max_path(t_lem_in *lem_in);

void	resolve(t_lem_in *lem_in)
{
	// if (/*start is connected to exit*/)
	// {
	// 	// throw all ants to exit at once
	// 	//return
	// }

	// From short paths to long paths
	for (int lenght = min_lenght(lem_in); lenght <= max_lenght(lem_in); lenght++)
	{
		// Try with all possible number of paths
		for (int nb_path = 1 ; nb_path <= max_path(lem_in) ; nb_path++)
		{
			// Try all the legal sum of path lenghts
			for (int i = 0; i < nb_path; i++)
			{
				int	sum = nb_path * lenght - lem_in->nb_ants - i;
				int nb_tuples = 0;
				int **scenari = tuples(sum, nb_path, &nb_tuples);

				ft_printf("%d - %d\n", sum, nb_path);
				for (int i = 0; i < nb_tuples; i++)
				{
					for (int j = 0; j < lenght; j++)
					{
						ft_printf("%d ", scenari[i][j]);
					}
					ft_printf("\n");
				}
				ft_printf("\n");


				// int **ptr_scenari = scenari;
				// while (*ptr_scenari)
				// {
				// 	int *ptr_scenario = *ptr_scenari;
				// 	while (*ptr_scenario)
				// 	{
				// 		for (/* all permutation of the scenario */)
				// 			if (/* permutation is valid */)
				// 				return (/* permutation */);
				// 		*ptr_scenario++;
				// 	}
				// 	ptr_scenari++;
				// }
				free_tuples(scenari, nb_tuples);
			}
		}
	}
}

int	min_lenght(t_lem_in *lem_in)
{
	(void)lem_in;
	return (1);
}

int	max_lenght(t_lem_in *lem_in)
{
	(void)lem_in;
	return (10);
}

int	max_path(t_lem_in *lem_in)
{
	(void)lem_in;
	return (5);
}

// int main() {
// 	int count;
// 	int ***my_tuples = tuples(2, 1, &count)
// }

static void free_tuples(int** tuples, int count)
{
    for (int i = 0; i < count; i++) {
        free(tuples[i]);
    }
    free(tuples);
}

static void generate_tuple(int* tuple, int index, int current_sum, int** tuples, int* tuples_count, int tuples_capacity, int size, int sum)
{
	if (index == size) {
		if (current_sum == sum) {
			if (*tuples_count == tuples_capacity) {
				tuples_capacity *= 2;
				int** new_tuples = (int**)malloc(tuples_capacity * sizeof(int*));
				ft_memcpy(new_tuples, tuples, *tuples_count * sizeof(int*));
				free(tuples);
				tuples = new_tuples;
			}
			tuples[*tuples_count] = (int*)malloc(size * sizeof(int));
			for (int i = 0; i < size; i++) {
				tuples[*tuples_count][i] = tuple[i];
			}
			(*tuples_count)++;
		}
		return;
	}

	for (int i = 1; i <= sum - current_sum; i++) {
		tuple[index] = i;
		generate_tuple(tuple, index + 1, current_sum + i, tuples, tuples_count, tuples_capacity, size, sum);
	}
}

static int **tuples(int sum, int size , int *count)
{
	int** tuples = NULL;
    int tuples_count = 0;
    int tuples_capacity = 32;

    tuples = (int**)malloc(tuples_capacity * sizeof(int*));

    int* tuple = (int*)malloc(size * sizeof(int));
    generate_tuple(tuple, 0, 0, tuples, &tuples_count, tuples_capacity, size, sum);
	free(tuple);
    *count = tuples_count;
    return tuples;
}
