/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:50:21 by iCARUS            #+#    #+#             */
/*   Updated: 2023/11/10 11:48:29 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualiser.h"

void	handle_inputs(mlx_key_data_t keydata, void* param)
{
	t_param *params = param;

	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(params->mlx);
	if (keydata.key == MLX_KEY_LEFT_SHIFT && keydata.action == MLX_PRESS)
	{
		params->zoom->scroll_direction = 'x';
	}
	if (keydata.key == MLX_KEY_LEFT_SHIFT && keydata.action == MLX_RELEASE)
	{
		params->zoom->scroll_direction = 'y';
	}
	if (keydata.key == MLX_KEY_LEFT_CONTROL && keydata.action == MLX_PRESS)
	{
		params->zoom->scroll_mode = 'z';
	}
	if (keydata.key == MLX_KEY_LEFT_CONTROL && keydata.action == MLX_RELEASE)
	{
		params->zoom->scroll_mode = 's';
	}
}
void	handle_window_close(void* param)
{
	mlx_t *mlx = (mlx_t *)param;

	mlx_close_window(mlx);
}

void	scroll_handler(double xdelta, double ydelta, void* param)
{
	t_param *params = param;

	params->last_redraw_request_age = 0;
	if (params->zoom->scroll_mode == 'z')
	{
		params->zoom->zoom_ratio *= (1 + (xdelta + ydelta) / 10) ;
		if (params->zoom->zoom_ratio < 0.1)
			params->zoom->zoom_ratio = 0.1;
	}
	else
	{	if (params->zoom->scroll_direction == 'x')
			params->zoom->x_offset += (xdelta + ydelta) * SCROLL_POWER;
		else
			params->zoom->y_offset += (xdelta + ydelta) * SCROLL_POWER;
	}
	params->need_to_redraw = true;

	return;
}

void	loop_handler(void* param)
{
	t_param *params = param;

	params->last_redraw_request_age += params->mlx->delta_time;
	if (params->last_redraw_request_age > 0.05 && params->need_to_redraw)
	{
		generate_image(params->mlx, &params->img, params->bg, params->zoom);
		params->need_to_redraw = false;
	}
}

void	resize_window(int width, int height, void* param)
{
	(void) width;
	(void) height;
	t_param *params = param;

	params->last_redraw_request_age = 0;
	params->need_to_redraw = true;
}
