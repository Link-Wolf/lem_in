/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Link <Link@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:14:15 by Link           #+#    #+#             */
/*   Updated: 2023/10/17 13:25:41 by Link          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"

void parse_file(void);
void process_cmd(char *line, int *cmd);
void porcess_ants(char *line);
void process_rooms(char *line);
void process_links(char *line);

#endif