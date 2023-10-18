/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: link <link@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:31:48 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/18 12:30:05 by link             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "structures.h"
# include "return_codes.h"
# include "../libft/libft.h"

/**
 *	@brief	Initialize the main room structure
 *	@return	A pointer to the structure
 *	@note	Must call tini() to free it
 */
t_room	**init(void);
/**
 *	@brief	Free the main room structure
 */
void	tini(t_lem_in *lem_in);
void	bugs(t_lem_in *lem_in, int code);
void	print_lemin(t_lem_in *lemin);
void	print_rooms(t_room *room);
void	print_links(t_room *room);

#endif
