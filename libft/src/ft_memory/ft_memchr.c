/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:22:46 by iCARUS            #+#    #+#             */
/*   Updated: 2022/11/28 08:52:11 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_memory.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n)
	{
		if (*(char *) s == (char) c)
			return ((void *) s);
		s++;
		n--;
	}
	return (NULL);
}
