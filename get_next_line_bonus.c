/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 23:21:40 by lfranca-          #+#    #+#             */
/*   Updated: 2021/06/30 23:39:53 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	copy_stored(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!dst || !src)
		return ;
	i = 0;
	while (*(src + i) && dstsize && i + 1 < dstsize)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	*(dst + i) = '\0';
}

int	get_cut_line(char **line, char *str, char *buff)

{
	int		index;
	int		str_len;

	index = 0;
	free(buff);
	while (str[index] != '\n')
	{
		index ++;
	}
	str_len = ft_strlen(str);
	*line = ft_substr(str, 0, index);
	index++;
	copy_stored(str, str + index, str_len + 1);
	return (1);
}

int	get_read_file(int fd, char **line, char *buff, char **stored)
{
	int		ret;
	char	*str_tmp;

	ret = read(fd, buff, BUFFER_SIZE);
	while (ret > 0)
	{
		buff[ret] = '\0';
		if (*stored)
		{
			str_tmp = ft_strjoin(*stored, buff);
			free(*stored);
			*stored = str_tmp;
		}
		else
			*stored = ft_strdup (buff);
		if (ft_strchr (*stored, '\n'))
			return (get_cut_line (line, *stored, buff));
		else
			ret = read(fd, buff, BUFFER_SIZE);
	}
	return (ret);
}

void	stored_to_line(int fd, char **line, char **str)
{
	*line = ft_strdup(str[fd]);
	free(str[fd]);
	str[fd] = NULL;
}

int	get_next_line(int fd, char **line)
{
	static char	*stored[MAX_FD];
	char		*buff;
	int			ret;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd < 0 || fd >= MAX_FD || !line || BUFFER_SIZE < 1
		|| read(fd, stored[fd], 0) < 0)
	{
		free(buff);
		return (-1);
	}
	if (stored[fd] && ft_strchr (stored[fd], '\n'))
		return (get_cut_line (line, stored[fd], buff));
	ret = get_read_file(fd, line, buff, &stored[fd]);
	if (ret == 1)
		return (1);
	free(buff);
	if (stored[fd])
	{
		stored_to_line(fd, line, stored);
		return (ret);
	}
	*line = ft_strdup("");
	return (ret);
}
