/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:18:42 by Link           #+#    #+#             */
/*   Updated: 2023/11/11 15:22:40 by iCARUS           ###   ########.fr       */
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
int			throw_ants(t_mode silent);
void		resolve();

#endif
