/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bugs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:20:02 by event             #+#    #+#             */
/*   Updated: 2023/10/17 14:24:46 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/init.h"
#include "../includes/codes.h"

void	bugs(t_lem_in *lem_in, int code)
{
	if (code == ERR_NAME_CONFLICT)
		ft_putendl_fd("ERROR: Room name conflict", 2);
	tini(lem_in);
	exit(code);
}