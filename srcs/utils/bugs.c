/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bugs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: link <link@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:20:02 by event             #+#    #+#             */
/*   Updated: 2023/10/18 12:30:00 by link             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	bugs(t_lem_in *lem_in, int code)
{
	if (code == ERR_ROOM_ALREADY_EXISTS)
		ft_putendl_fd("ERROR: Room name conflict", 2);
	tini(lem_in);
	exit(code);
}
