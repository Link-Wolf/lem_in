/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: link <link@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:07:17 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/18 14:08:38 by link             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# define NAME_SIZE 128

typedef struct s_room
{
	int				is_entry;
	int				is_exit;
	int				nb_linked;
	int				max_linked;
	int				x_coord;
	int				y_coord;
	char			name[NAME_SIZE + 1];
	struct s_room	*left;
	struct s_room	*right;
	struct s_room	**linked_rooms;
}	t_room;

typedef struct s_lem_in
{
	int		nb_ants;
	t_room	**rooms;
	t_room	*start;
	t_room	*exit;
}	t_lem_in;

#endif