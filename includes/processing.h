/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:18:42 by Link           #+#    #+#             */
/*   Updated: 2023/11/14 16:29:24 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESSING_H
# define PROCESSING_H

# include "../libs/libft/libft.h"
# include "./structures.h"
# include "./return_codes.h"
# include "./utils.h"
# include <limits.h>

void	check_for_trivials();
int		throw_ants(t_mode silent);
void	resolve();
int		make_ants_advance(t_ant *ants, int nb_ants_sent, t_mode silent);
void	fill_ultimate_definitive_edition_deluxe_master_path(t_ultimate_definitive_edition_deluxe_master_path *ant_pathes);

void	sort_ant_pathes(t_ultimate_definitive_edition_deluxe_master_path **ant_pathes, int nb_pathes);

void 	init_ant_path_send(t_ultimate_definitive_edition_deluxe_master_path **ant_pathes, int nb_pathes, int total_ants);
void		delete_ultimate_definitive_edition_deluxe_master_path(t_ultimate_definitive_edition_deluxe_master_path *ant_pathes);


#endif
