/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: link <link@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 08:39:42 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/18 15:24:04 by link             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include "ft_printf.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2048
# endif

size_t	zek_strlen(char const *str);
char	*zek_check(char *memory, int fd);
char	*get_next_line(int fd);
char	*zek_get_next(char *str);
char	*zek_get_line(char *str);
char	*zek_free(char *str);

#endif
