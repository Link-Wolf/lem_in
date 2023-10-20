/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Link <Link@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:18:42 by Link           #+#    #+#             */
/*   Updated: 2023/10/20 15:04:31 by Link          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESSING_H
# define PROCESSING_H

# include "../libft/libft.h"
# include "./structures.h"
# include "./return_codes.h"
# include "./utils.h"
# include <limits.h>

int		check_for_trivials(t_lem_in *lem_in);
void	evaluate_distances(t_lem_in *lem_in);
void	throw_ants(t_lem_in *lemin);

#endif
