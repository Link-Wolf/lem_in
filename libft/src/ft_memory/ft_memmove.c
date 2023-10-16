/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Link <Link@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:23:04 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/16 17:36:13 by Link          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_memory.h"

void *ft_memmove(void *dst, const void *src, size_t len)
{
	size_t i;
	int step;

	if (dst == NULL && src == NULL)
		return (NULL);
	if (len > 0 && dst != src)
	{
		i = 0;
		step = 1;
		if (src < dst)
		{
			i = len - 1;
			step = -1;
		}
		while (i < len)
		{
			((char *)dst)[i] = ((char *)src)[i];
			i += step;
		}
	}
	return (dst);
}
