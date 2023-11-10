/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 08:41:40 by iCARUS            #+#    #+#             */
/*   Updated: 2023/11/10 11:33:23 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H

/* Return absolute value of a */
int	ft_abs(int a);

/* Return the squareroot of nb */
int	ft_sqrt(int nb);

/* Return the max between a and b */
int	ft_max(int a, int b);

/* Return the min between a and b */
int	ft_min(int a, int b);

/* Return the sign of x*/
int	ft_sign(int x);

/**
 *	@brief	Quack fast inverse square root
 *	@param	x	The number inverse the square root to
 *	@return		A approximation of x^(-1/2)
 */
float	ft_rsqrt(float x);

#endif
