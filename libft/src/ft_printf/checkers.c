/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 09:33:28 by iCARUS            #+#    #+#             */
/*   Updated: 2022/11/30 07:35:20 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/_ft_printf.h"

/*
 *	is_conversion
 *
 *	check if a char is a conversion token or not
 *
 *	to_check:
 *		the char to check
 */
int	is_conversion(char to_check)
{
	return ((ft_strchr(FT_CONVERSIONS, to_check) != NULL));
}

/*
 *	is_flag
 *
 *	check if a char is a conversion flag or not
 *
 *	to_check:
 *		the char to check
 */
int	is_flag(char to_check)
{
	return (ft_strchr(FT_FLAGS, to_check) != NULL);
}
