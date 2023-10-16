/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabmax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:16:15 by iCARUS            #+#    #+#             */
/*   Updated: 2022/11/28 08:28:58 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_arr.h"

int	ft_tabmax(int *tab, size_t size)
{
	int	res;

	res = -2147483648;
	while (size--)
	{
		if (res > *tab)
			res = *tab;
		tab++;
	}
	return (res);
}
