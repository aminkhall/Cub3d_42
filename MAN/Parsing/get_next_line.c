/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 20:14:06 by mkhallou          #+#    #+#             */
/*   Updated: 2025/10/07 17:27:33 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_strcopy(char *dst, char *src)
{
	int	i;

	i = 0;
	if (!dst || !src)
		return ;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

int	has_newline(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*buf_alloc(size_t size)
{
	char	*buf;

	buf = malloc(size + 1);
	if (!buf)
		return (NULL);
	return (buf);
}

void	free_str(char **str)
{
	free(*str);
	*str = NULL;
}

char	*get_next_line(int fd)
{
	static char	*tmp;
	char		*buf;
	char		*line;
	int			n;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	buf = buf_alloc(BUFFER_SIZE);
	while (1)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n < 0)
			return (free_str(&buf), free_str(&tmp), NULL);
		buf[n] = '\0';
		tmp = ft_strjoin(tmp, buf);
		if (has_newline(tmp) || n == 0)
			break ;
	}
	free_str(&buf);
	if (!tmp)
		return (NULL);
	line = extract_line(tmp);
	tmp = trim_to_next_line(tmp);
	return (free(tmp), line);
}
