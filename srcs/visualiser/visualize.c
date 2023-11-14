/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:52:50 by iCARUS            #+#    #+#             */
/*   Updated: 2023/11/14 14:23:34 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visualiser.h"

#define	FIXED_WIDTH			1920
#define FIXED_HEIGHT		1080
#define	MARGIN				100
#define	RADIUS				60
#define	ROOM_BORDER_COLOR	0x000000FF
#define	ROOM_FILL_COLOR		0xFFFFFFFF
#define	ROOM_START_FILL		0x55FFFFFF
#define	ROOM_END_FILL		0xFF5555FF

extern t_lem_in *lem_in;

static void	inputs(mlx_key_data_t kydata, void* param);
static void	close_win(void* param);
static void	do_the_loop(void* param);
static void	init_background(mlx_image_t *background);
static void draw_pretty_rooms(t_room *room, mlx_image_t *bg);
// static void	fill_area(mlx_image_t *img, uint32_t x, uint32_t y, int color);
static void draw_pretty_links(t_room *room, mlx_image_t *bg);
static void	draw_thick_link(mlx_image_t *bg, t_room *start, t_room *end);
static void draw_ant(int x, int y, mlx_image_t *ants);
static void show_ants(double time, mlx_image_t *ants);
static void ants_finish(void);
static void hide_ants(double time);
void    visualize(t_mode mode)
{
    mlx_t       *mlx;
    mlx_image_t *background;
    mlx_image_t *ants;
    t_param     param;
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
    mlx_loop_hook(mlx, do_the_loop, &param);
    mlx_loop(mlx);
    mlx_terminate(mlx);
}
static void inputs(mlx_key_data_t keydata, void* param)
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
static void close_win(void* param)
{
    mlx_t *mlx = (mlx_t *)param;
    mlx_close_window(mlx);
}
static void do_the_loop(void* param)
{
    t_param *params = param;
    // if (!params->is_animating)
    //  return;
    hide_ants(params->time);
    params->time += params->mlx->delta_time;
    if (params->time > 1.0)
    {
     params->is_animating = 0;
     params->time = 0.0;
     ants_finish();
    }
    show_ants(params->time, params->ants);
}
static void hide_ants(double time)
{
    (void)time;
    //TODO:
}
static void ants_finish(void)
{
    //TODO:
}
static void show_ants(double time, mlx_image_t *ants)
{
    (void)time;
    //loop and sometimes :
    draw_ant(200, 200, ants);
    //TODO:
}
static void draw_ant(int x, int y, mlx_image_t *ants)
{
    x -= 7;
    y -= 11;
    uint32_t brown = 0x6E260EFF;
    uint32_t red = 0xFF672CFF;
    //antenne gauche
    set_pixel_color(get_pixel_address(ants, x + 4, y), red);
    set_pixel_color(get_pixel_address(ants, x + 4, y + 1), red);
    set_pixel_color(get_pixel_address(ants, x + 4, y + 2), red);
    set_pixel_color(get_pixel_address(ants, x + 5, y + 3), brown);
    //antenne droite
    set_pixel_color(get_pixel_address(ants, x + 10, y), red);
    set_pixel_color(get_pixel_address(ants, x + 10, y + 1), red);
    set_pixel_color(get_pixel_address(ants, x + 10, y + 2), red);
    set_pixel_color(get_pixel_address(ants, x + 9, y + 3), brown);
    //head
    set_pixel_color(get_pixel_address(ants, x + 6, y + 4), red);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 4), red);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 4), red);
    set_pixel_color(get_pixel_address(ants, x + 5, y + 5), red);
    set_pixel_color(get_pixel_address(ants, x + 6, y + 5), brown);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 5), red);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 5), brown);
    set_pixel_color(get_pixel_address(ants, x + 9, y + 5), red);
    set_pixel_color(get_pixel_address(ants, x + 5, y + 6), red);
    set_pixel_color(get_pixel_address(ants, x + 6, y + 6), red);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 6), red);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 6), red);
    set_pixel_color(get_pixel_address(ants, x + 9, y + 6), red);
    set_pixel_color(get_pixel_address(ants, x + 5, y + 7), red);
    set_pixel_color(get_pixel_address(ants, x + 6, y + 7), red);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 7), red);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 7), red);
    set_pixel_color(get_pixel_address(ants, x + 9, y + 7), red);
    set_pixel_color(get_pixel_address(ants, x + 6, y + 8), red);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 8), red);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 8), red);
    //patte avant gauche
    set_pixel_color(get_pixel_address(ants, x + 1, y + 4), brown);
    set_pixel_color(get_pixel_address(ants, x + 2, y + 5), brown);
    set_pixel_color(get_pixel_address(ants, x + 2, y + 6), brown);
    set_pixel_color(get_pixel_address(ants, x + 3, y + 7), brown);
    set_pixel_color(get_pixel_address(ants, x + 4, y + 8), brown);
    set_pixel_color(get_pixel_address(ants, x + 5, y + 9), brown);
    //patte avant droite
    set_pixel_color(get_pixel_address(ants, x + 9, y + 9), brown);
    set_pixel_color(get_pixel_address(ants, x + 10, y + 8), brown);
    set_pixel_color(get_pixel_address(ants, x + 11, y + 7), brown);
    set_pixel_color(get_pixel_address(ants, x + 12, y + 6), brown);
    set_pixel_color(get_pixel_address(ants, x + 12, y + 5), brown);
    set_pixel_color(get_pixel_address(ants, x + 13, y + 4), brown);
    //patte milieu gauche
    set_pixel_color(get_pixel_address(ants, x + 0, y + 9), brown);
    set_pixel_color(get_pixel_address(ants, x + 1, y + 9), brown);
    set_pixel_color(get_pixel_address(ants, x + 2, y + 10), brown);
    set_pixel_color(get_pixel_address(ants, x + 3, y + 11), brown);
    set_pixel_color(get_pixel_address(ants, x + 4, y + 11), brown);
    //patte milieu droite
    set_pixel_color(get_pixel_address(ants, x + 10, y + 11), brown);
    set_pixel_color(get_pixel_address(ants, x + 11, y + 11), brown);
    set_pixel_color(get_pixel_address(ants, x + 12, y + 10), brown);
    set_pixel_color(get_pixel_address(ants, x + 13, y + 9), brown);
    set_pixel_color(get_pixel_address(ants, x + 14, y + 9), brown);
    //corps
    set_pixel_color(get_pixel_address(ants, x + 6, y + 9), red);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 9), red);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 9), red);
    set_pixel_color(get_pixel_address(ants, x + 5, y + 10), red);
    set_pixel_color(get_pixel_address(ants, x + 6, y + 10), red);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 10), red);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 10), red);
    set_pixel_color(get_pixel_address(ants, x + 9, y + 10), red);
    set_pixel_color(get_pixel_address(ants, x + 5, y + 11), red);
    set_pixel_color(get_pixel_address(ants, x + 6, y + 11), red);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 11), red);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 11), red);
    set_pixel_color(get_pixel_address(ants, x + 9, y + 11), red);
    set_pixel_color(get_pixel_address(ants, x + 5, y + 12), red);
    set_pixel_color(get_pixel_address(ants, x + 6, y + 12), red);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 12), red);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 12), red);
    set_pixel_color(get_pixel_address(ants, x + 9, y + 12), red);
    //patte arriere gauche
    set_pixel_color(get_pixel_address(ants, x + 4, y + 13), brown);
    set_pixel_color(get_pixel_address(ants, x + 3, y + 14), brown);
    set_pixel_color(get_pixel_address(ants, x + 2, y + 15), brown);
    set_pixel_color(get_pixel_address(ants, x + 2, y + 16), brown);
    set_pixel_color(get_pixel_address(ants, x + 1, y + 17), brown);
    //patte arriere droite
    set_pixel_color(get_pixel_address(ants, x + 10, y + 13), brown);
    set_pixel_color(get_pixel_address(ants, x + 11, y + 14), brown);
    set_pixel_color(get_pixel_address(ants, x + 12, y + 15), brown);
    set_pixel_color(get_pixel_address(ants, x + 12, y + 16), brown);
    set_pixel_color(get_pixel_address(ants, x + 13, y + 17), brown);
    //queue
    set_pixel_color(get_pixel_address(ants, x + 6, y + 13), brown);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 13), brown);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 13), brown);
    set_pixel_color(get_pixel_address(ants, x + 6, y + 14), red);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 14), red);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 14), red);
    set_pixel_color(get_pixel_address(ants, x + 5, y + 15), red);
    set_pixel_color(get_pixel_address(ants, x + 6, y + 15), red);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 15), red);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 15), red);
    set_pixel_color(get_pixel_address(ants, x + 9, y + 15), red);
    set_pixel_color(get_pixel_address(ants, x + 5, y + 16), brown);
    set_pixel_color(get_pixel_address(ants, x + 6, y + 16), brown);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 16), brown);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 16), brown);
    set_pixel_color(get_pixel_address(ants, x + 9, y + 16), brown);
    set_pixel_color(get_pixel_address(ants, x + 5, y + 17), red);
    set_pixel_color(get_pixel_address(ants, x + 6, y + 17), red);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 17), red);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 17), red);
    set_pixel_color(get_pixel_address(ants, x + 9, y + 17), red);
    set_pixel_color(get_pixel_address(ants, x + 5, y + 18), brown);
    set_pixel_color(get_pixel_address(ants, x + 6, y + 18), brown);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 18), brown);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 18), brown);
    set_pixel_color(get_pixel_address(ants, x + 9, y + 18), brown);
    set_pixel_color(get_pixel_address(ants, x + 5, y + 19), red);
    set_pixel_color(get_pixel_address(ants, x + 6, y + 19), red);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 19), red);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 19), red);
    set_pixel_color(get_pixel_address(ants, x + 9, y + 19), red);
    set_pixel_color(get_pixel_address(ants, x + 6, y + 20), red);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 20), red);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 20), red);
}

static void	init_background(mlx_image_t *background)
{
	for (uint32_t i = 0; i < background->width; i++)
		for (uint32_t j = 0; j < background->height; j++)
			set_pixel_color(get_pixel_address(background, i, j), 0x000000FF);
	draw_pretty_links(*lem_in->rooms, background);
	draw_pretty_rooms(*lem_in->rooms, background);
}

static void draw_pretty_rooms(t_room *room, mlx_image_t *bg)
{
	if (!room)
		return ;
	draw_pretty_rooms(room->left, bg);
	draw_pretty_rooms(room->right, bg);
	for (int x = -RADIUS; x <= RADIUS;x++)
		for (int y = -RADIUS; y <= RADIUS;y++)
			if (x * x + y * y < RADIUS * RADIUS)
			{
				set_pixel_color(
					get_pixel_address(bg, x + room->x_coord, y + room->og_y_coord),
					room->is_end ? ROOM_END_FILL : room->is_start ? ROOM_START_FILL : ROOM_FILL_COLOR
				);
			}
	draw_room(bg,
		room->x_coord,
		room->og_y_coord,
		RADIUS * 2, ROOM_BORDER_COLOR);

}

// static void	fill_area(mlx_image_t *img, uint32_t x, uint32_t y, int color)
// {
// 	uint8_t	*pxl_address = get_pixel_address(img, x, y);

// 	if (x >= img->width
// 		|| y >= img->height
// 		|| *((u_int32_t *) pxl_address) == 0x000000FF)
// 	return ;
// 	fill_area(img, x + 1, y, color);
// 	fill_area(img, x - 1, y, color);
// 	fill_area(img, x, y + 1, color);
// 	fill_area(img, x, y - 1, color);
// 	set_pixel_color(pxl_address, color);
// }

static void draw_pretty_links(t_room *room, mlx_image_t *bg)
{
	if (!room)
		return ;
	for (int i = 0; i < room->nb_linked; i++)
	{
		draw_thick_link(bg, room, room->linked_rooms[i]);
	}
	draw_pretty_links(room->left, bg);
	draw_pretty_links(room->right, bg);
}

static void	draw_thick_link(mlx_image_t *bg, t_room *start, t_room *end)
{
	int	x_step = 0;
	int y_step = 0;
	int	delta_x = ft_abs(start->x_coord - end->x_coord);
	int	delta_y = ft_abs(start->og_y_coord - end->og_y_coord);

	if (delta_x > delta_y)
		y_step = 1;
	else
		x_step = 1;

	for (int i = -2; i <= 2; i++)
		draw_link(
			bg,
			start->x_coord + x_step * i, start->og_y_coord + y_step * i,
			end->x_coord + x_step * i, end->og_y_coord + y_step * i,
			ROOM_FILL_COLOR
		);
	draw_link(
			bg,
			start->x_coord + x_step * -3, start->og_y_coord + y_step * -3,
			end->x_coord + x_step * -3, end->og_y_coord + y_step * -3,
			ROOM_BORDER_COLOR
		);
	draw_link(
			bg,
			start->x_coord + x_step * 3, start->og_y_coord + y_step * 3,
			end->x_coord + x_step * 3, end->og_y_coord + y_step * 3,
			ROOM_BORDER_COLOR
		);
}
