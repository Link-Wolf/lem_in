/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:18:42 by Link           #+#    #+#             */
/*   Updated: 2023/11/08 15:32:38 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESSING_H
# define PROCESSING_H

# include "../libs/libft/libft.h"
# include "./structures.h"
# include "./return_codes.h"
# include "./utils.h"
# include <limits.h>

void		check_for_trivials();
void		evaluate_distances();
void		throw_ants();
void		resolve();

#endif
