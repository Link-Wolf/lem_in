/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualiser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:42:25 by iCARUS            #+#    #+#             */
/*   Updated: 2023/11/09 13:27:00 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALISER_H
# define VISUALISER_H

# include "../libs/libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <MLX42/MLX42.h>
# include <time.h>
# include "utils.h"
# include "return_codes.h"
# include "structures.h"

# define WIDTH 2200
# define HEIGHT 2021
# define DESIRED_ROOM_SIZE 80
# define SPACE_BETWEEN_ROOMS 120
# define START_ROOM_COLOR 0xFF0000FF
# define EXIT_ROOM_COLOR 0x0000FFFF
# define SPACE_BETWEEN_LINES 5
# define ROOM_COLOR 0x904D50FF

# define MARGIN_SIZE 80
# define ROOM_DIAMETER 80
# define SCROLL_POWER 40

typedef	struct	s_zoom
{
	char	scroll_direction;
	char	scroll_mode;
	int		width;
	int		height;
	double	x_offset;
	double	y_offset;
	double	zoom_ratio;
}				t_zoom;

typedef	struct	s_param{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_zoom			*zoom;
	double			last_redraw_request_age;
	bool			need_to_redraw;
}					t_param;

void 	visualise();

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

/**
 *	@brief Draw all rooms by calling draw_room for each room.
 *	@param room The first room of the list.
 *	@param img The image to draw in.
 *	@param room_size The diameter of the rooms.
 *	@param lemin The lem_in structure.
 *	@param width The width of the window ? maybe :shrug:
 */
void draw_all_rooms(t_room *room, mlx_image_t *img, int room_size, int width, t_zoom *zoom);

/**
 *	@brief Draw all links by calling draw_link for each link.
 *	@param room The first room of the list.
 *	@param img The image to draw in.
 *	@param room_size The diameter of the rooms.
 *	@param lemin The lem_in structure.
 *	@param width The width of the window ? maybe :shrug:
 */
void draw_all_links(t_room *room, mlx_image_t *img, int room_size, int width, t_zoom *zoom);

/**
 * 	@brief Handle the inputs of the user inside a mlx loop.
 * 	@param keydata The keydata structure.
 * 	@param param The param structure.
 */
void	handle_inputs(mlx_key_data_t keydata, void* param);

/**
 *	@brief Handle the window's resize behavior
 *	@param param The param structure.
 */
void	loop_handler(void* param);

/**
 * 	@brief Handle the window's resize signal but can't do a lot itself 'cause it's dumb
 * 	@param width The new width of the window.
 * 	@param height The new height of the window.
 * 	@param param The param structure.
 */
void	resize_window(int width, int height, void* param);

/**
 *	@brief Handle the window's close signal.
 *	@param param The param structure.
 */
void	handle_window_close(void* param);

/**
 * 	@brief Handle the mouse's scroll behavior.
 * 	@param xdelta The x delta of the scroll.
 * 	@param ydelta The y delta of the scroll.
 * 	@param param The param structure.
 */
void	scroll_handler(double xdelta, double ydelta, void* param);

/**
 * 	@brief (Re)generate the image. from scratch.
 * 	@param mlx The mlx structure.
 * 	@param img The image structure.
 * 	@param zoom The zoom structure.
 * 	@param lemin The lem_in structure.
 */
void	generate_image(mlx_t *mlx, mlx_image_t **img, t_zoom *zoom);

/**
 * 	@brief Generate a random color.
 * 	@return The random color.
 */
int 	get_random_color(void);

/**
 *	@brief draw room names
 */
void draw_room_names(t_room *room, mlx_t *mlx, int width, t_zoom *zoom);

#endif
