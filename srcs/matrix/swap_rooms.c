/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:34:45 by iCARUS            #+#    #+#             */
/*   Updated: 2023/11/01 10:40:56 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/matrix.h"

void	swap_rooms(t_room_matrix *matrix, int i, int j)
{
	int	tmp;

	if (i >= matrix->dimension || j >= matrix->dimension)
		return ;
	if (i == j)
		return ;
	tmp = matrix->swaps[i];
	matrix->swaps[i] = matrix->swaps[j];
	matrix->swaps[j] = tmp;
}
