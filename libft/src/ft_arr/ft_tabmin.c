/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabmin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:16:10 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/24 15:59:25 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_arr.h"

int	ft_tabmin(int *tab, size_t size)
{
	int	res;

	res = 2147483647;
	while (size--)
	{
		if (res > *tab)
			res = *tab;
		tab++;
	}
	return (res);
}
