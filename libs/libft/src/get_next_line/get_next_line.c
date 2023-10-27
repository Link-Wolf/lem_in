/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: link <link@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 09:25:13 by iCARUS            #+#    #+#             */
/*   Updated: 2023/10/18 15:25:52 by link             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/get_next_line.h"

size_t	zek_strlen(char const *str)
{
	size_t	i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
	}
	return (i);
}

char	*zek_strjoin(char *s1, char *s2, int i, int j)
{
	char		*temp;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		s1[i] = '\0';
	}
	if (!s2 || !s1)
		return (NULL);
	temp = (char *)malloc(sizeof(char) * (zek_strlen(s1) + zek_strlen(s2) + 1));
	if (!temp)
		return (NULL);
	while (s1[i])
	{
		temp[i] = s1[i];
		i++;
	}
	while (s2[++j])
		temp[i + j] = s2[j];
	temp[i + j] = '\0';
	free(s1);
	return (temp);
}

char	*zek_get_line(char	*str)
{
	char		*temp;
	int			i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	temp = (char *)malloc(sizeof(char) * (i + 2));
	if (!temp)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		temp[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		temp[i] = str[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*zek_get_next(char *str)
{
	char		*temp;
	int			i;
	int			j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (zek_free(str));
	temp = (char *)malloc(sizeof(char) * (zek_strlen(str) - i));
	if (!temp)
		return (NULL);
	j = i + 1;
	while (str[++i])
		temp[i - j] = str[i];
	temp[i - j] = '\0';
	free(str);
	return (temp);
}

int	zek_strchr(char *str, char c)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == c)
				return (i);
			i++;
		}
	}
	return (-1);
}

char	*zek_check(char *memory, int fd)
{
	char	*buffer;
	int		bytescopy;

	bytescopy = 1;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (zek_strchr(memory, '\n') <= 0 && bytescopy)
	{
		bytescopy = read(fd, buffer, BUFFER_SIZE);
		if (bytescopy == -1)
			return (zek_free(buffer));
		buffer[bytescopy] = '\0';
		memory = zek_strjoin(memory, buffer, 0, -1);
	}
	free(buffer);
	return (memory);
}

char	*get_next_line(int fd)
{
	static char	*memory = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	memory = zek_check(memory, fd);
	if (!memory)
		return (zek_free(memory));
	line = zek_get_line(memory);
	memory = zek_get_next(memory);
	return (line);
}

char	*zek_free(char *str)
{
	free(str);
	return (NULL);
}
