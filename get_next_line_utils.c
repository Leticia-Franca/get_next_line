/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:31:58 by lfranca-          #+#    #+#             */
/*   Updated: 2021/06/30 21:44:26 by lfranca-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	len;
	char	*ptr_s;

	i = 0;
	ptr_s = (char *)s;
	len = ft_strlen(ptr_s);
	while (i < len)
	{
		if (ptr_s[i] == (char)c)
		{
			return (&ptr_s[i]);
		}
		i++;
	}
	if (ptr_s[i] == (char)c)
		return (&ptr_s[i]);
	else
		return (NULL);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	sum_sizes;
	char	*new_s;

	if (!s1 || !s2)
		return (NULL);
	sum_sizes = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_s = (char *)malloc(sum_sizes);
	i = 0;
	j = 0;
	if (new_s == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		new_s[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		new_s[i + j] = s2[j];
		j++;
	}
	new_s[i + j] = '\0';
	return (new_s);
}

char	*ft_strdup(const char *s)
{
	char	*new_s;
	char	*p;
	int		i;

	i = 0;
	p = (char *)s;
	new_s = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (new_s == NULL)
		return (NULL);
	while (p[i] != '\0')
	{
		new_s[i] = p[i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_string;
	size_t	i;
	size_t	s_leng;

	if (!s)
		return (NULL);
	s_leng = ft_strlen(s);
	if (s == NULL || s_leng <= start)
		return (ft_strdup(""));
	if (start + len < s_leng)
		new_string = (char *)malloc(sizeof(char) * (len + 1));
	else
		new_string = (char *)malloc(sizeof(char) * (s_leng - start + 1));
	if (new_string == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		new_string[i] = s[start + i];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}
