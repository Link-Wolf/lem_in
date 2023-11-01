/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cell.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:26:29 by iCARUS            #+#    #+#             */
/*   Updated: 2023/11/01 11:13:10 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/matrix.h"

int	get_cell(t_room_matrix *matrix, int i, int j)
{
	if (i >= matrix->dimension || j >= matrix->dimension)
		return (INT_MIN);
	return (matrix->matrix[matrix->swaps[i]][matrix->swaps[j]]);
}

void	set_cell(t_room_matrix *matrix, int i, int j, int value)
{
	if (i >= matrix->dimension || j >= matrix->dimension)
		return ;
	matrix->matrix[matrix->swaps[i]][matrix->swaps[j]] = value;
	matrix->matrix[matrix->swaps[j]][matrix->swaps[i]] = value;
}
