/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:24:27 by iCARUS            #+#    #+#             */
/*   Updated: 2022/11/28 09:49:21 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_string.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*res;

	res = malloc ((len + 1) * sizeof (char));
	if (!res || !s)
		return (NULL);
	i = -1;
	while (++i < len && s[start + i])
		res[i] = s[start + i];
	res[i] = '\0';
	if (start >= ft_strlen(s))
		res[0] = '\0';
	return (res);
}
