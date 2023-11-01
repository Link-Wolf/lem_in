/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:21:12 by iCARUS            #+#    #+#             */
/*   Updated: 2023/11/01 10:41:10 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
#define MATRIX_H

#include <limits.h>
#include "../libs/libft/libft.h"
#include "./structures.h"

/**
 *	@brief Create a matrix of dimension x dimension
 *	@param dimension The dimension of the matrix
 *	@return The matrix created or NULL if an error occured
 */
t_room_matrix	*create_matrix(int dimension);

/**
 *	@brief Destroy a matrix
 *	@param matrix The matrix to destroy
 */
void			destroy_matrix(t_room_matrix *matrix);

/**
 *	@brief Get the value of a cell in a matrix
 *	@param matrix The matrix
 *	@param i The row of the cell
 *	@param j The column of the cell
 *	@return The value of the cell
 */
int				get_cell(t_room_matrix *matrix, int i, int j);

/**
 *	@brief Set the value of a cell in a matrix
 *	@param matrix The matrix
 *	@param i The row of the cell
 *	@param j The column of the cell
 *	@param value The value to set
 */
void			set_cell(t_room_matrix *matrix, int i, int j, int value);

/**
 *	@brief Print a matrix
 *	@param matrix The matrix to print
 */
void			print_matrix(t_room_matrix *matrix);

/**
 *	@brief Swap two rooms in a matrix
 *	@param matrix The matrix
 *	@param i The index of the first room
 *	@param j The index of the second room
 */
void	swap_rooms(t_room_matrix *matrix, int i, int j);

#endif
