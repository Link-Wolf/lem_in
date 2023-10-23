/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:18:42 by Link           #+#    #+#             */
/*   Updated: 2023/10/23 13:39:33 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESSING_H
# define PROCESSING_H

# include "../libft/libft.h"
# include "./structures.h"
# include "./return_codes.h"
# include "./utils.h"
# include <limits.h>

void		check_for_trivials(t_lem_in *lem_in);
void		evaluate_distances(t_lem_in *lem_in);
void		throw_ants(t_lem_in *lemin);
void		manage_conflicts(t_lem_in *lem_in);
void		create_pathes(t_lem_in *lem_in);
void 		sort_pathes(t_lem_in *lem_in);
t_pathes	*create_path(t_room *room, int pseudo_index, t_pathes *parent, int depth, t_lem_in *s_lem_in);

#endif
