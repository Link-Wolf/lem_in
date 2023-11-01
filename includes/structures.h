/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:07:17 by iCARUS            #+#    #+#             */
/*   Updated: 2023/11/01 10:59:51 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# define NAME_SIZE 128

struct s_pathes;
struct s_visualiser;

typedef struct s_room_matrix
{
	int	dimension;
	int	*swaps;
	int	**matrix;
} t_room_matrix;

typedef struct s_room
{
	// Basic stuff
	char			name[NAME_SIZE + 1];
	int				id;
	int				is_start;
	int				is_end;

	// Tree stuff
	struct s_room	*left;
	struct s_room	*right;

	// Visualizer stuff
	int				x_coord;
	int				y_coord;
	int				*distances_to_ends;
	int				nb_linked;
	int				max_linked;
	struct s_room	**linked_rooms;
}	t_room;

typedef struct s_visualiser
{
	int max_y;
	int max_x;

	int nb_allocated_room_lines;
	int	*room_line_size;

}	t_visualiser;

typedef struct s_lem_in
{
	// Options
	int				verbose;
	int				has_visualizer;

	// Counter
	int				nb_rooms;
	int				nb_links;
	int				nb_ants;

	// Room tree
	t_room			**rooms;
	t_room			*start;
	t_room			*end;

	// Room matrix
	t_room_matrix	*matrix;

	// Visualizer
	t_visualiser	*visualiser;
}	t_lem_in;

typedef struct s_ant
{
	int			id;
	int			wait_turns;
	int			is_arrived;

	// Add a way to know where she is and where she is going
} t_ant;

#endif
