/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:52:50 by iCARUS            #+#    #+#             */
/*   Updated: 2023/11/14 17:56:27 by iCARUS           ###   ########.fr       */
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
static void draw_ant(int x, int y, mlx_image_t *ants, uint32_t color1, uint32_t color2);
static void show_or_hide_ants(double time, mlx_image_t *ants, bool show);
static void ants_finish(t_mode mode);
static void	init_ants(mlx_image_t *ants, t_mode mode);
static void draw_finished(mlx_t *mlx);

int														total_ants;
int														nb_ants_sent;
int														nb_turn;
int														nb_ants_arrived;
int														nb_pathes = 0;
t_ant													*ants;
t_ultimate_definitive_edition_deluxe_master_path		**ant_pathes;

void    visualize(t_mode mode)
{
    mlx_t       *mlx;
    mlx_image_t *background;
    mlx_image_t *ants_img;
    t_param     param;
    if (!(mlx = mlx_init(FIXED_WIDTH, FIXED_HEIGHT, "lem-in", false)))
        bugs(ERR_MLX_INIT);
    if (!(background = mlx_new_image(mlx, FIXED_WIDTH, FIXED_HEIGHT)))
        bugs(ERR_MLX_NEW_IMG);
    if (!(ants_img = mlx_new_image(mlx, FIXED_WIDTH, FIXED_HEIGHT)))
        bugs(ERR_MLX_NEW_IMG);
    init_background(background);
	init_ants(ants_img, mode);
    if (mlx_image_to_window(mlx, background, 0, 0) == -1)
        bugs(ERR_MLX_IMG_TO_WIN);
    if (mlx_image_to_window(mlx, ants_img, 0, 0) == -1)
        bugs(ERR_MLX_IMG_TO_WIN);
    param.mlx = mlx;
    param.ants = ants_img;
    param.time = 0.0;
    param.is_animating = false;
    param.mode = mode;
    mlx_close_hook(mlx, close_win, mlx);
    mlx_key_hook(mlx, inputs, &param);
    mlx_loop_hook(mlx, do_the_loop, &param);
    mlx_loop(mlx);
    mlx_terminate(mlx);
	free(ants);
	for (int i = 0; i < nb_pathes; i++)
		delete_ultimate_definitive_edition_deluxe_master_path(ant_pathes[i]);
	free(ant_pathes);
	if (lem_in->verbose && mode == DEFAULT)
		ft_printf("#Solved in %d turns fro %d ants for %d rooms\n", nb_turn, total_ants, lem_in->nb_rooms);
}

static void	init_ants(mlx_image_t *ants_img, t_mode mode)
{
	ft_bzero(ants_img->pixels, sizeof (uint8_t) * 4 * ants_img->width * ants_img->height);
	total_ants = lem_in->nb_ants;
	if (mode == DEFAULT)
		ft_printf("# There are %d ants.\n", total_ants);

	ants = ft_calloc(sizeof(t_ant), total_ants);
	if (!ants)
		bugs(ERR_ALLOCATION);
	for (int i = 0; i < lem_in->graph->source->nb_outing_edges; i++)
	{
		t_edge *edge = lem_in->graph->source->outing_edges[i];
		if (edge->flow)
			nb_pathes++;
	}
	ant_pathes = malloc(sizeof(t_ultimate_definitive_edition_deluxe_master_path *) * nb_pathes);
	if (!ant_pathes)
		bugs(ERR_ALLOCATION);

	int k = 0;
	for (int i = 0; i < lem_in->start->nb_linked; i++)
	{
		t_room	*pseudo_entry = lem_in->start->linked_rooms[i];
		t_edge	*inner_edge = NULL;
		for (int j = 0; j < pseudo_entry->in_node->nb_outing_edges; j++)
		{
			if (!pseudo_entry->in_node->outing_edges[j]->is_reversal_edge)
			{
				inner_edge = pseudo_entry->in_node->outing_edges[j];
				break;
			}
		}
		if (inner_edge && inner_edge->flow)
		{
			ant_pathes[k] = malloc(sizeof(t_ultimate_definitive_edition_deluxe_master_path));
			if (!ant_pathes[k])
				bugs(ERR_ALLOCATION);
			ant_pathes[k++]->room = inner_edge->in->room;
		}
	}

	while (--k >= 0)
	{
		fill_ultimate_definitive_edition_deluxe_master_path(ant_pathes[k]);
	}

	sort_ant_pathes(ant_pathes, nb_pathes);

	init_ant_path_send(ant_pathes, nb_pathes, total_ants);

	nb_ants_sent = 0;
	nb_turn = -1; // The first round is a init_round with no ant movement
	nb_ants_arrived = 0;
	ants_finish(mode);
	show_or_hide_ants(0, ants_img, 1);
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

static void draw_finished(mlx_t *mlx)
{
	mlx_put_string(mlx, "FINISHED UwU", 900, 100);
}
static void do_the_loop(void* param)
{
    t_param *params = param;
	if (nb_ants_arrived == total_ants)
	{
		draw_finished(params->mlx);
		return;
	}
    if (!params->is_animating)
    	return;
    show_or_hide_ants(params->time, params->ants, 0);
    params->time += params->mlx->delta_time;
	if (nb_ants_sent < total_ants)
		draw_ant(lem_in->start->x_coord, lem_in->start->og_y_coord, params->ants, 0xFF0000FF, 0x6E260EFF);
	else
		draw_ant(lem_in->start->x_coord, lem_in->start->og_y_coord, params->ants, 0x00000000, 0x00000000);
    if (params->time > 1.0)
    {
    	params->is_animating = 0;
    	params->time = 0.0;
    	ants_finish(params->mode);
		if (nb_ants_arrived)
			draw_ant(lem_in->end->x_coord, lem_in->end->og_y_coord, params->ants, 0xFF0000FF, 0x6E260EFF);
		else
			draw_ant(lem_in->end->x_coord, lem_in->end->og_y_coord, params->ants, 0x00000000, 0x00000000);
    }
    show_or_hide_ants(params->time, params->ants, 1);
}
static void ants_finish(t_mode mode)
{
    nb_ants_arrived += make_ants_advance(ants, nb_ants_sent, mode);
	for (int i = 0; i < nb_pathes; i++)
	{
		if (nb_ants_sent >= total_ants)
			break;
		if (ant_pathes[i]->ants)
		{
			ants[nb_ants_sent].current_room = lem_in->start;
			ants[nb_ants_sent].path = ant_pathes[i];
			ants[nb_ants_sent].is_arrived = 0;
			ant_pathes[i]->ants--;
			nb_ants_sent++;
		}
	}
	nb_turn++;
}
static void show_or_hide_ants(double time, mlx_image_t *ants_img, bool show)
{
    for (int i = 0; i < nb_ants_sent; i++)
	{
		if (ants[i].is_arrived || !ants[i].path->room)
			continue;
		int	x_pos = ants[i].current_room->x_coord * (1 - time) + ants[i].path->room->x_coord * time;
		int	y_pos = ants[i].current_room->og_y_coord * (1 - time) + ants[i].path->room->og_y_coord * time;
		draw_ant(x_pos, y_pos, ants_img,
			(show ? 0xFF0000FF : 0x00000000), (show ? 0x6E260EFF : 0x00000000));
	}
}
static void draw_ant(int x, int y, mlx_image_t *ants, uint32_t color1, uint32_t color2)
{
    x -= 7;
    y -= 11;

	if (x < 15 || x >= (int) ants->width - 15
		|| y  < 21 || y  >= (int) ants->height - 21)
					return ;

    //antenne gauche
    set_pixel_color(get_pixel_address(ants, x + 4, y), color1);
    set_pixel_color(get_pixel_address(ants, x + 4, y + 1), color1);
    set_pixel_color(get_pixel_address(ants, x + 4, y + 2), color1);
    set_pixel_color(get_pixel_address(ants, x + 5, y + 3), color2);
    //antenne droite
    set_pixel_color(get_pixel_address(ants, x + 10, y), color1);
    set_pixel_color(get_pixel_address(ants, x + 10, y + 1), color1);
    set_pixel_color(get_pixel_address(ants, x + 10, y + 2), color1);
    set_pixel_color(get_pixel_address(ants, x + 9, y + 3), color2);
    //head
    set_pixel_color(get_pixel_address(ants, x + 6, y + 4), color1);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 4), color1);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 4), color1);
    set_pixel_color(get_pixel_address(ants, x + 5, y + 5), color1);
    set_pixel_color(get_pixel_address(ants, x + 6, y + 5), color2);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 5), color1);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 5), color2);
    set_pixel_color(get_pixel_address(ants, x + 9, y + 5), color1);
    set_pixel_color(get_pixel_address(ants, x + 5, y + 6), color1);
    set_pixel_color(get_pixel_address(ants, x + 6, y + 6), color1);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 6), color1);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 6), color1);
    set_pixel_color(get_pixel_address(ants, x + 9, y + 6), color1);
    set_pixel_color(get_pixel_address(ants, x + 5, y + 7), color1);
    set_pixel_color(get_pixel_address(ants, x + 6, y + 7), color1);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 7), color1);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 7), color1);
    set_pixel_color(get_pixel_address(ants, x + 9, y + 7), color1);
    set_pixel_color(get_pixel_address(ants, x + 6, y + 8), color1);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 8), color1);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 8), color1);
    //patte avant gauche
    set_pixel_color(get_pixel_address(ants, x + 1, y + 4), color2);
    set_pixel_color(get_pixel_address(ants, x + 2, y + 5), color2);
    set_pixel_color(get_pixel_address(ants, x + 2, y + 6), color2);
    set_pixel_color(get_pixel_address(ants, x + 3, y + 7), color2);
    set_pixel_color(get_pixel_address(ants, x + 4, y + 8), color2);
    set_pixel_color(get_pixel_address(ants, x + 5, y + 9), color2);
    //patte avant droite
    set_pixel_color(get_pixel_address(ants, x + 9, y + 9), color2);
    set_pixel_color(get_pixel_address(ants, x + 10, y + 8), color2);
    set_pixel_color(get_pixel_address(ants, x + 11, y + 7), color2);
    set_pixel_color(get_pixel_address(ants, x + 12, y + 6), color2);
    set_pixel_color(get_pixel_address(ants, x + 12, y + 5), color2);
    set_pixel_color(get_pixel_address(ants, x + 13, y + 4), color2);
    //patte milieu gauche
    set_pixel_color(get_pixel_address(ants, x + 0, y + 9), color2);
    set_pixel_color(get_pixel_address(ants, x + 1, y + 9), color2);
    set_pixel_color(get_pixel_address(ants, x + 2, y + 10), color2);
    set_pixel_color(get_pixel_address(ants, x + 3, y + 11), color2);
    set_pixel_color(get_pixel_address(ants, x + 4, y + 11), color2);
    //patte milieu droite
    set_pixel_color(get_pixel_address(ants, x + 10, y + 11), color2);
    set_pixel_color(get_pixel_address(ants, x + 11, y + 11), color2);
    set_pixel_color(get_pixel_address(ants, x + 12, y + 10), color2);
    set_pixel_color(get_pixel_address(ants, x + 13, y + 9), color2);
    set_pixel_color(get_pixel_address(ants, x + 14, y + 9), color2);
    //corps
    set_pixel_color(get_pixel_address(ants, x + 6, y + 9), color1);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 9), color1);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 9), color1);
    set_pixel_color(get_pixel_address(ants, x + 5, y + 10), color1);
    set_pixel_color(get_pixel_address(ants, x + 6, y + 10), color1);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 10), color1);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 10), color1);
    set_pixel_color(get_pixel_address(ants, x + 9, y + 10), color1);
    set_pixel_color(get_pixel_address(ants, x + 5, y + 11), color1);
    set_pixel_color(get_pixel_address(ants, x + 6, y + 11), color1);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 11), color1);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 11), color1);
    set_pixel_color(get_pixel_address(ants, x + 9, y + 11), color1);
    set_pixel_color(get_pixel_address(ants, x + 5, y + 12), color1);
    set_pixel_color(get_pixel_address(ants, x + 6, y + 12), color1);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 12), color1);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 12), color1);
    set_pixel_color(get_pixel_address(ants, x + 9, y + 12), color1);
    //patte arriere gauche
    set_pixel_color(get_pixel_address(ants, x + 4, y + 13), color2);
    set_pixel_color(get_pixel_address(ants, x + 3, y + 14), color2);
    set_pixel_color(get_pixel_address(ants, x + 2, y + 15), color2);
    set_pixel_color(get_pixel_address(ants, x + 2, y + 16), color2);
    set_pixel_color(get_pixel_address(ants, x + 1, y + 17), color2);
    //patte arriere droite
    set_pixel_color(get_pixel_address(ants, x + 10, y + 13), color2);
    set_pixel_color(get_pixel_address(ants, x + 11, y + 14), color2);
    set_pixel_color(get_pixel_address(ants, x + 12, y + 15), color2);
    set_pixel_color(get_pixel_address(ants, x + 12, y + 16), color2);
    set_pixel_color(get_pixel_address(ants, x + 13, y + 17), color2);
    //queue
    set_pixel_color(get_pixel_address(ants, x + 6, y + 13), color2);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 13), color2);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 13), color2);
    set_pixel_color(get_pixel_address(ants, x + 6, y + 14), color1);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 14), color1);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 14), color1);
    set_pixel_color(get_pixel_address(ants, x + 5, y + 15), color1);
    set_pixel_color(get_pixel_address(ants, x + 6, y + 15), color1);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 15), color1);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 15), color1);
    set_pixel_color(get_pixel_address(ants, x + 9, y + 15), color1);
    set_pixel_color(get_pixel_address(ants, x + 5, y + 16), color2);
    set_pixel_color(get_pixel_address(ants, x + 6, y + 16), color2);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 16), color2);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 16), color2);
    set_pixel_color(get_pixel_address(ants, x + 9, y + 16), color2);
    set_pixel_color(get_pixel_address(ants, x + 5, y + 17), color1);
    set_pixel_color(get_pixel_address(ants, x + 6, y + 17), color1);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 17), color1);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 17), color1);
    set_pixel_color(get_pixel_address(ants, x + 9, y + 17), color1);
    set_pixel_color(get_pixel_address(ants, x + 5, y + 18), color2);
    set_pixel_color(get_pixel_address(ants, x + 6, y + 18), color2);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 18), color2);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 18), color2);
    set_pixel_color(get_pixel_address(ants, x + 9, y + 18), color2);
    set_pixel_color(get_pixel_address(ants, x + 5, y + 19), color1);
    set_pixel_color(get_pixel_address(ants, x + 6, y + 19), color1);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 19), color1);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 19), color1);
    set_pixel_color(get_pixel_address(ants, x + 9, y + 19), color1);
    set_pixel_color(get_pixel_address(ants, x + 6, y + 20), color1);
    set_pixel_color(get_pixel_address(ants, x + 7, y + 20), color1);
    set_pixel_color(get_pixel_address(ants, x + 8, y + 20), color1);
}

static void	init_background(mlx_image_t *background)
{
	for (uint32_t i = 0; i < background->width; i++)
		for (uint32_t j = 0; j < background->height; j++)
			set_pixel_color(get_pixel_address(background, i, j), 0x555555FF);
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
				if (x + room->x_coord < 0 || x + room->x_coord >= (int) bg->width
					|| y + room->og_y_coord < 0 || y + room->og_y_coord >= (int) bg->height)
					continue;
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
