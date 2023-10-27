/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:07:17 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/27 16:40:42 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# define NAME_SIZE 128

struct s_pathes;
struct s_visualiser;

typedef struct s_room
{
	char			name[NAME_SIZE + 1];
	int				is_start;
	int				is_end;
	int				x_coord;
	int				y_coord;
	int				*distances_to_ends;

	struct s_room	*left;
	struct s_room	*right;

	int				nb_linked;
	int				max_linked;
	struct s_room	**linked_rooms;

	int				nb_path_users;
	int				max_path_users;
	struct s_pathes	**path_users;
}	t_room;

typedef struct s_pathes
{
	int				is_motherfucking_good;
	int				depth;
	t_room			*room;
	struct s_pathes	*parent; // NULL if path is pseudo exit

	int				nb_children;
	int				max_children;
	struct s_pathes	**children;

	int				nb_conflicts;
	int				max_conflicts;
	struct s_pathes	**conflicts;
}	t_pathes;

typedef struct s_visualiser
{
	int max_y;
	int max_x;

	int nb_allocated_room_lines;
	int	*room_line_size;

}	t_visualiser;

typedef struct s_lem_in
{
	int				nb_rooms;
	int				nb_links;
	int				verbose;
	int				has_visualizer;
	t_pathes		**def_paths;
	t_room			**rooms;
	t_room			*start;
	t_room			*end;

	int				nb_def_paths;
	int				nb_ants;
	t_pathes		**pathes; // NOTE: act as a tree

	int				*nb_pathes_leaves;
	int				*max_pathes_leaves;
	t_pathes		***good_pathes; // NOTE: act as an array
	t_visualiser	*visualiser;
}	t_lem_in;

typedef struct s_ant
{
	int				id;
	struct s_pathes	*where_to_go;
	int				wait_turns;
	int				is_arrived;
} t_ant;

typedef struct s_state
{
	int	value;
	int	*state;
	int	state_size;
}	t_state;


#endif
