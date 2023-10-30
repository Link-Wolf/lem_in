/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:50:21 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/30 11:07:22 by iCARUS           ###   ########.fr       */
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

// static int point_in_circle(int x, int y, int cx, int cy, int r)
// {
// 	int radius_squared = r * r;
// 	int distance_center_point_squared = (x - cx) * (x - cx) + (y - cy) * (y - cy);

// 	return (distance_center_point_squared <= radius_squared);
// }

static void set_pixel_color(uint8_t *pixel, int color)
{
	pixel[0] = get_r(color);
	pixel[1] = get_g(color);
	pixel[2] = get_b(color);
	pixel[3] = get_a(color);
}

static uint8_t *get_pixel_address(mlx_image_t *img, int x, int y)
{
	return img->pixels + (x + y * img->width) * 4;
}

void	draw_room(mlx_image_t *img, int x, int y, int d, int color)
{
	int E = -d/2;
	int X = d/2;
	int Y = 0;

	while (Y <= X)
	{
		for (int i = -1 ; i <= 1 ; i += 2) // left right reflexion
		{
			for (int j = -1 ; j <= 1 ; j += 2) // up down reflexion
			{
				for (int k = 0; k < d * 5; k++) // fill the circle (5 is arbitrary)
				{
					int pixel_x = x + i * X * k / d / 5;
					int pixel_y = y + j * Y * k / d / 5;
					if (pixel_x >= 0 && pixel_x < (int) img->width
						&& pixel_y >= 0 && pixel_y < (int) img->height)
						set_pixel_color(
							get_pixel_address(
								img, pixel_x, pixel_y), // X >= Y octants
							color);
					pixel_x = x + i * Y * k / d / 5;
					pixel_y = y + j * X * k / d / 5;
					if (pixel_x >= 0 && pixel_x < (int) img->width
						&& pixel_y >= 0 && pixel_y < (int) img->height)
						set_pixel_color(
							get_pixel_address(
								img, pixel_x, pixel_y), // X <= Y octants
							color);
					}
			}
		}

		E += 2 * Y + 1;
		Y++;
		if (E >= 0)
		{
			E -= 2 * X - 1;
			X--;
		}
	}
}

static void	plotLineLow(mlx_image_t *img, int x0, int y0, int x1, int y1, int color)
{
	int	dx = x1 - x0;
	int	dy = y1 - y0;
	int	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	int	D = (2 * dy) - dx;
	int	y = y0;

	for (int x = x0; x <= x1 ; x++)
	{
		if (x >= 0 && x < (int) img->width
			&& y >= 0 && y < (int) img->height)
			set_pixel_color(get_pixel_address(img, x, y), color);
		if (D > 0)
		{
			y = y + yi;
			D = D + (2 * (dy - dx));
		}
		else
			D = D + 2*dy;
	}
}


static void	plotLineHigh(mlx_image_t *img, int x0, int y0, int x1, int y1, int color)
{
	int	dx = x1 - x0;
	int	dy = y1 - y0;
	int	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	int	D = (2 * dx) - dy;
	int	x = x0;

	for (int y = y0; y <= y1 ; y++)
    {
		if (x >= 0 && x < (int) img->width
			&& y >= 0 && y < (int) img->height)
			set_pixel_color(get_pixel_address(img, x, y), color);
        if (D > 0)
        {
			x = x + xi;
            D = D + (2 * (dx - dy));
		}
        else
            D = D + 2*dx;
	}
}

void	draw_link(mlx_image_t *img, int x0, int y0, int x1, int y1, int color)
{
	if (ft_abs(y1 - y0) < ft_abs(x1 - x0))
    {
		if (x0 > x1)
            plotLineLow(img, x1, y1, x0, y0, color);
        else
            plotLineLow(img, x0, y0, x1, y1, color);
	}
    else
	{
        if (y0 > y1)
            plotLineHigh(img, x1, y1, x0, y0, color);
        else
            plotLineHigh(img, x0, y0, x1, y1, color);
	}
}
