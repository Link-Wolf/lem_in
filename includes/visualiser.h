/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualiser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:42:25 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/30 10:39:24 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALISER_H
# define VISUALISER_H

# include "../libs/libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <MLX42/MLX42.h>
# include "utils.h"
# include "return_codes.h"
# include "structures.h"

# define WIDTH 3840
# define HEIGHT 2160
# define DESIRED_ROOM_SIZE 80
# define SPACE_BETWEEN_ROOMS 80
# define ROOM_COLOR 0x00FF00FF

void 	visualise(t_lem_in *lemin);

/**
 *	@brief Draw a room in the image. Using Breseham's midpoint algorithm.
 *	@param img The image to draw in.
 *	@param x The x coordinate of the center of the room.
 *	@param y The y coordinate of the center of the room.
 *	@param d The diameter of the room.
 *	@param color The color of the room.
 */
void	draw_room(mlx_image_t *img, int x, int y, int d, int color);

/**
 *	@brief Draw a link between two rooms. Using Breseham's line algorithm.
 *	@param img The image to draw in.
 *	@param x1 The x coordinate of the first room.
 *	@param y1 The y coordinate of the first room.
 *	@param x2 The x coordinate of the second room.
 *	@param y2 The y coordinate of the second room.
 *	@param color The color of the link.
 */
void	draw_link(mlx_image_t *img, int x1, int y1, int x2, int y2, int color);

#endif
