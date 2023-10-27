/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualiser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:42:25 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/27 17:40:32 by iCARUS           ###   ########.fr       */
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
void	draw_room(mlx_image_t *img, int x, int y, int d, int color);

#endif
