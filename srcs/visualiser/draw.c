/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:50:21 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/27 17:13:12 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualiser.h"

// Get the red channel.
static int get_r(int rgba)
{
    // Move 3 bytes to the right and mask out the first byte.
    return ((rgba >> 24) & 0xFF);
}

// Get the green channel.
static int get_g(int rgba)
{
    // Move 2 bytes to the right and mask out the first byte.
    return ((rgba >> 16) & 0xFF);
}

// Get the blue channel.
static int get_b(int rgba)
{
    // Move 1 byte to the right and mask out the first byte.
    return ((rgba >> 8) & 0xFF);
}

// Get the alpha channel.
static int get_a(int rgba)
{
    // Move 0 bytes to the right and mask out the first byte.
    return (rgba & 0xFF);
}

static int point_in_circle(int x, int y, int cx, int cy, int r)
{
	int radius_squared = r * r;
	int distance_center_point_squared = (x - cx) * (x - cx) + (y - cy) * (y - cy);

	return (distance_center_point_squared <= radius_squared);
}

static void set_pixel_color(uint8_t *pixel, int color)
{
	pixel[0] = get_r(color);
	pixel[1] = get_g(color);
	pixel[2] = get_b(color);
	pixel[3] = get_a(color);
}

void	draw_room(mlx_image_t *img, int x, int y, int d, int color)
{
	//ft_printf("draw_room x = %d, y = %d, d = %d\n", x, y, d);
	for (int i = x - d / 2; i < x + d / 2; i++)
	{
		for (int j = y - d / 2; j < y + d / 2; j++)
		{
			if (i >= 0 && i < (int) img->width && j >= 0 && j < (int) img->height
				&& point_in_circle(i, j, x, y, d / 2)
			)
				set_pixel_color(img->pixels + (i + j * img->width) * 4, color);
		}
	}
}
