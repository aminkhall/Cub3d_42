/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymisbah <aymisbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 20:14:03 by mkhallou          #+#    #+#             */
/*   Updated: 2025/08/14 12:47:57 by aymisbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	result = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
		return (free_str(&s1), NULL);
	ft_strcopy(result, s1);
	ft_strcopy(result + ft_strlen(s1), s2);
	return (free_str(&s1), result);
}

char	*ft_strdup(char *s)
{
	char	*copy;

	if (!s)
		return (NULL);
	copy = malloc(ft_strlen(s) + 1);
	if (!copy)
		return (NULL);
	ft_strcopy(copy, s);
	return (copy);
}

int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

char	*extract_line(char *line)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	if (!line || !*line)
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (ft_strdup(line));
	result = malloc(i + 1);
	if (!result)
		return (NULL);
	j = 0;
	while (j < i)
	{
		result[j] = line[j];
		j++;
	}
	result[j] = '\0';
	return (result);
}

char	*trim_to_next_line(char *line)
{
	char	*result;
	int		i;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (free_str(&line), NULL);
	i++;
	result = ft_strdup(line + i);
	return (free_str(&line), result);
}
