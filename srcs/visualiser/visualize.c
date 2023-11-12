/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:52:50 by iCARUS            #+#    #+#             */
/*   Updated: 2023/11/12 16:28:02 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualiser.h"

#define	FIXED_WIDTH		1920
#define FIXED_HEIGHT	1080
#define	MARGIN			100
#define	RADIUS			30

extern t_lem_in *lem_in;

static void	inputs(mlx_key_data_t kydata, void* param);
static void	close_win(void* param);
static void	loop(void* param);
static void	init_background(mlx_image_t *background);
static void evaluate_min_max(t_room *room, int *min_x, int *max_x, int *min_y, int *max_y);

void	visualize(t_mode mode)
{
	mlx_t		*mlx;
	mlx_image_t	*background;
	mlx_image_t	*ants;
	t_param		param;

	if (!(mlx = mlx_init(FIXED_WIDTH, FIXED_HEIGHT, "lem-in", false)))
		bugs(ERR_MLX_INIT);
	if (!(background = mlx_new_image(mlx, FIXED_WIDTH, FIXED_HEIGHT)))
		bugs(ERR_MLX_NEW_IMG);
	if (!(ants = mlx_new_image(mlx, FIXED_WIDTH, FIXED_HEIGHT)))
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
	param.mode = mode;

	mlx_close_hook(mlx, close_win, mlx);
	mlx_key_hook(mlx, inputs, &param);
	mlx_loop_hook(mlx, loop, &param);
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

static void	loop(void* param)
{
	t_param *params = param;

	if (!params->is_animating)
		return;
	// hide_ants(params->time);
	params->time += params->mlx->delta_time;
	if (params->time > 1.0)
	{
		params->is_animating = 0;
		params->time = 0.0;
		// ants_finish();
	}
	// show_ants(params->time);
}

static void	init_background(mlx_image_t *background)
{
	int	min_x = INT_MAX;
	int	max_x = INT_MIN;
	int	min_y = INT_MAX;
	int	max_y = INT_MIN;
	double	cell_width;
	double	cell_height;

	evaluate_min_max(lem_in->start, &min_x, &max_x, &min_y, &max_y);
	cell_width = ((double) FIXED_WIDTH - MARGIN) / ((double) max_x - min_x - 1);
	cell_height = ((double) FIXED_HEIGHT - MARGIN) / ((double) max_y - min_y - 1);
	for (unsigned int i = MARGIN / 2; i <= background->width - MARGIN / 2; i += cell_width)
		for (unsigned int j = MARGIN / 2; j <= background->height - MARGIN / 2; j += cell_height)
		{
			set_pixel_color(
				get_pixel_address(background, i, j),
				0xFF0000FF
			);
		}
}

static void evaluate_min_max(t_room *room, int *min_x, int *max_x, int *min_y, int *max_y)
{
	if (!room)
		return;
	evaluate_min_max(room->left, min_x, max_x, min_y, max_y);
	evaluate_min_max(room->right, min_x, max_x, min_y, max_y);
	if (*max_x < room->x_coord)
		*max_x = room->x_coord;
	if (*min_x > room->x_coord)
		*min_x = room->x_coord;
	if (*max_y < room->og_y_coord)
		*max_y = room->og_y_coord;
	if (*min_y > room->og_y_coord)
		*min_y = room->og_y_coord;
}
