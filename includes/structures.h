/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:07:17 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/17 11:27:45 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_room
{
	int		is_entry;
	int		is_exit;
	char	*name;
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
