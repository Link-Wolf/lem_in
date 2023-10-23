/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_pathes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:33:38 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/23 18:00:44 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/processing.h"

static void insertionSort(t_pathes *arr[], int n);

void sort_pathes(t_lem_in *lem_in)
{
	for (int i = 0; i < lem_in->end->nb_linked; i++)
	{
		insertionSort(lem_in->good_pathes[i], lem_in->nb_pathes_leaves[i]);
	}
}

static void insertionSort(t_pathes *arr[], int n)
{
	int i, j;
	t_pathes *key;

	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j]->depth > key->depth)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}
