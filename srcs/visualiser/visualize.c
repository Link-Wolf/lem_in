/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:52:50 by iCARUS            #+#    #+#             */
/*   Updated: 2023/11/12 15:17:43 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualiser.h"

#define	WIDTH	1920
#define HEIGHT	1080

extern t_lem_in *lem_in;

static void	inputs(mlx_key_data_t kydata, void* param);
static void	close_win(void* param);
static void	loop_handler(void* param);
static void	init_background(mlt_image_t *background);

void	visualize(t_mode mode)
{
	t_mlx		*mlx;
	t_mlx_image	*background;
	t_mlx_image	*ants;
	t_param		param;

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "lem-in", false)))
		bugs(ERR_MLX_INIT);
	if (!(background = mlx_new_image(mlx, WIDTH, HEIGHT)))
		bugs(ERR_MLX_NEW_IMG);
	if (!(ants = mlx_new_image(mlx, WIDTH, HEIGHT)))
		bugs(ERR_MLX_NEW_IMG);
	init_background(background);
	if (mlx_image_to_window(mlx, background, 0, 0) == -1)
		bugs(ERR_MLX_IMG_TO_WIN);
	if (mlx_image_to_window(mlx, ants, 0, 0) == -1)
		bugs(ERR_MLX_IMG_TO_WIN);
	param.mlx = mlx;
	param.ants = ants;
	param.time = 0.0;
	param.is_animating = false;

	mlx_close_hook(mlx, close_win, mlx);
	mlx_key_hook(mlx, inputs, &params);
	mlx_loop_hook(mlx, loop, &params);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
static void	inputs(mlx_key_data_t keydata, void* param)
{
	t_param *params = param;

	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(params->mlx);
	if (!params->is_animating && keydata.key == MLX_KEY_SPACE)
	{
		params->is_animating = 1;
		params->time = 0;
	}
}
static void	close_win(void* param)
{
	mlx_t *mlx = (mlx_t *)param;

	mlx_close_window(mlx);
}

static void	loop_handler(void* param)
{
	t_param *params = param;

	if (!params->is_animating)
		return;
	hide_ants(params->time);
	params->time += params->mlx->delta_time;
	if (params->time > 1.0)
	{
		params->is_animating = 0;
		params->time = 0.0;
		ants_finish();
	}
	show_ants(params->time);
}

static void	init_background(mlt_image_t *background)
{
	int	min_x = INT_MAX;
	int	max_x = INT_MIN;
	int	min_y = INT_MAX;
	int	max_y = INT_MIN;


}
