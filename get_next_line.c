/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 22:08:40 by lfranca-          #+#    #+#             */
/*   Updated: 2021/06/30 18:19:56 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_strcpy(char *dst, const char *src, size_t dstsize)
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

int	cut_line(char **line, char *str, char *buff)
{
	int	str_len;
	int	index;

	index = 0;
	free(buff);
	while (str[index] != '\n')
	{
		index++;
	}
	str_len = ft_strlen(str);
	*line = ft_substr(str, 0, index);
	index++;
	ft_strcpy(str, str + index, str_len + 1);
	return (1);
}

int	get_read(int fd, char **line, char *buff, char **str)
{
	int		ret;
	char	*str_tmp;

	ret = read(fd, buff, BUFFER_SIZE);
	while (ret > 0)
	{
		*(buff + ret) = '\0';
		if (*str)
		{
			str_tmp = ft_strjoin(*str, buff);
			free(*str);
			*str = str_tmp;
		}
		else
			*str = ft_strdup(buff);
		if (ft_strchr(*str, '\n'))
			return (cut_line(line, *str, buff));
		else
			ret = read(fd, buff, BUFFER_SIZE);
	}
	return (ret);
}

void	stored_to_line(char **line, char **str)
{
	*line = ft_strdup(*str);
	free(*str);
	*str = NULL;
}

int	get_next_line(int fd, char **line)
{
	static char	*stored;
	char		*buff;
	int			ret;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (-1);
	if (fd < 0 || !line || BUFFER_SIZE < 1 || read(fd, stored, 0) < 0)
	{
		free(buff);
		return (-1);
	}
	if (stored && ft_strchr(stored, '\n'))
		return (cut_line(line, stored, buff));
	ret = get_read(fd, line, buff, &stored);
	if (ret == 1)
		return (1);
	free(buff);
	if (stored)
	{
		stored_to_line(line, &stored);
		return (ret);
	}
	*line = ft_strdup("");
	return (ret);
}
