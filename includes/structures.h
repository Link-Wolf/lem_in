/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Link <Link@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:07:17 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/20 17:24:35 by Link          ###   ########.fr       */
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
	t_room			*room;
	struct s_pathes	*parent;
	struct s_pathes	**children;
}	t_pathes;

typedef struct s_lem_in
{
	int			nb_ants;
	t_pathes	**pathes;
	t_room		**rooms;
	t_room		*start;
	t_room		*end;
}	t_lem_in;

#endif
