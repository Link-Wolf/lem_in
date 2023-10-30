/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:50:21 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/30 17:40:51 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualiser.h"

void	handle_inputs(mlx_key_data_t keydata, void* param)
{
	mlx_t *mlx = param;

	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(mlx);

}
void	handle_window_close(void* param)
{
	mlx_t *mlx = (mlx_t *)param;

	mlx_close_window(mlx);
}

void	scroll_handler(double xdelta, double ydelta, void* param)
{
	t_param *params = param;

	if (ydelta != 0) {
		// scroll up or down, move the content of the img vertically as ydelta * constant
		params->zoom->y += ydelta * 10;
		generate_image(params->mlx, &params->img, params->zoom, params->lemin);
	}

	if (xdelta != 0) {
		// scroll left or right, move the content of the img horizontally as xdelta * constant
		params->zoom->x += xdelta * 10;
		generate_image(params->mlx, &params->img, params->zoom, params->lemin);
	}

	return;
}

void	loop_handler(void* param)
{
	t_param *params = param;

	params->last_resize_age += params->mlx->delta_time;
	if (params->last_resize_age > 0.05 && params->need_to_resize)
	{
		generate_image(params->mlx, &params->img, params->zoom, params->lemin);
		params->need_to_resize = false;
	}
}

void	resize_window(int width, int height, void* param)
{
	(void) width;
	(void) height;
	t_param *params = param;

	params->last_resize_age = 0;
	params->need_to_resize = true;
}
