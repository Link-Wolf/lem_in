/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atobuf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 07:54:40 by iCARUS            #+#    #+#             */
/*   Updated: 2022/12/05 09:36:14 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_cast.h"

t_buff	*ft_atobuf(char *str)
{
	t_buff	*ret;

	ret = ft_calloc(1, sizeof(t_buff));
	ret->data = ft_strdup(str);
	ret->len = ft_strlen(ret->data);
	return (ret);
}
