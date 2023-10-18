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

size_t	ft_strlen(char const *str);
char	*ft_check(char *memory, int fd);
char	*get_next_line(int fd);
char	*ft_get_next(char *str);
char	*ft_get_line(char *str);
char	*ft_free(char *str);
char	*zek_strjoin(char *s1, char *s2, int i, int j);

#endif
