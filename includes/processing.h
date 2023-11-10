/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:18:42 by Link           #+#    #+#             */
/*   Updated: 2023/11/10 10:49:44 by iCARUS           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESSING_H
# define PROCESSING_H

# include "../libs/libft/libft.h"
# include "./structures.h"
# include "./return_codes.h"
# include "./utils.h"
# include <limits.h>

typedef enum e_mode {
	DEFAULT,
	SILENT
} t_mode;

void		check_for_trivials();
void		evaluate_distances();
int			throw_ants(t_mode silent);
void		resolve();

#endif
