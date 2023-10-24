/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:07:17 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/24 15:21:28 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# define NAME_SIZE 128

typedef struct s_room
{
	int				is_start;
	int				is_end;
	int				nb_linked;
	int				max_linked;
	int				x_coord;
	int				y_coord;
	char			name[NAME_SIZE + 1];
	struct s_room	*left;
	struct s_room	*right;
	struct s_room	**linked_rooms;
	int				*distances_to_ends;
}	t_room;

typedef struct s_pathes
{
	int				nb_children;
	int				max_children;
	int				is_motherfucking_good;
	int				depth;
	t_room			*room;
	struct s_pathes	*parent; // NULL if pathe is pseudo exit
	struct s_pathes	**children;
}	t_pathes;

typedef struct s_lem_in
{
	int			verbose;
	int			nb_def_paths;
	t_pathes	**def_paths;
	int			nb_ants;
	t_pathes	**pathes; // NOTE: act as a tree
	int			*nb_pathes_leaves;
	int			*max_pathes_leaves;
	t_pathes	***good_pathes; // NOTE: act as an array
	t_room		**rooms;
	t_room		*start;
	t_room		*end;
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
