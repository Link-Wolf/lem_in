/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:07:17 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/17 15:13:29 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# define NAME_SIZE 128

typedef struct s_room
{
	int		is_entry;
	int		is_exit;
	int		nb_linked;
	int		max_linked;
	char	name[NAME_SIZE + 1];
	t_room	*left;
	t_room	*right;
	t_room	*linked_rooms;
}	t_room;

typedef struct s_lem_in
{
	int		nb_ants;
	t_room	**rooms;
	t_room	*start;
	t_room	*exit;
}	t_lem_in;

#endif
