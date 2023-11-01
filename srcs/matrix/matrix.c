/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:20:47 by iCARUS            #+#    #+#             */
/*   Updated: 2023/11/01 11:18:26 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/matrix.h"

t_room_matrix	*create_matrix(int dimension)
{
	t_room_matrix	*matrix;

	matrix = malloc(sizeof(t_room_matrix));
	if (!matrix)
		return (NULL);
	matrix->dimension = dimension;
	matrix->swaps = malloc(sizeof(int) * dimension);
	matrix->matrix = ft_calloc(dimension, sizeof(int *));
	if (!matrix->matrix || !matrix->swaps)
	{
		free(matrix->matrix);
		free(matrix->swaps);
		free(matrix);
		return (NULL);
	}
	for (int i = 0; i < dimension; i++)
	{
		matrix->matrix[i] = ft_calloc(dimension, sizeof(int));
		if (!matrix->matrix[i])
		{
			for (int j = 0 ; j < i; j++)
				free(matrix->matrix[j]);
			free(matrix->matrix);
			free(matrix->swaps);
			free(matrix);
			return (NULL);
		}
		matrix->matrix[i][i] = -1;
		matrix->swaps[i] = i;
	}
	return (matrix);
}

void	delete_matrix(t_room_matrix *matrix)
{
	for (int i = 0; i < matrix->dimension; i++)
		free(matrix->matrix[i]);
	free(matrix->matrix);
	free(matrix->swaps);
	free(matrix);
}

void	print_matrix(t_room_matrix *matrix)
{
	for (int i = 0; i < matrix->dimension; i++)
	{
		for (int j = 0; j < matrix->dimension; j++)
			ft_printf("%02d ", get_cell(matrix, i, j));
		ft_printf("\n");
	}
}
