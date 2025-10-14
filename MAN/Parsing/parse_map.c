/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 20:11:03 by mkhallou          #+#    #+#             */
/*   Updated: 2025/10/07 17:26:22 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_map(char *str)
{
	if (!str || !(*str))
		return (0);
	while (*str && *str == ' ')
		++str;
	if (*str == '1')
		return (1);
	return (0);
}

int	valid_map(char *str)
{
	int		i;
	int		len;
	char	c;

	if (!str || !(*str))
		return (0);
	len = ft_strlen(str);
	i = 0;
	while (str[i] && str[i] == ' ')
		++i;
	while (len && str[len - 1] == ' ')
		--len;
	if (str[i] != '1' || str[len - 1] != '1')
		return (0);
	while (str[i])
	{
		c = str[i];
		if (c != '1' && c != '0' && c != 'N' && c != 'E' && c != 'S' && c != 'W'
			&& c != ' ')
			return (0);
		++i;
	}
	return (1);
}

char	**fill_map(char *str, char **map, int *height)
{
	char	**new_map;
	int		i;

	if (!str || !(*str))
		return (0);
	new_map = malloc(sizeof(char *) * ((*height) + 2));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < (*height))
	{
		new_map[i] = map[i];
		++i;
	}
	++(*height);
	new_map[i] = ft_strdup(str);
	new_map[++i] = NULL;
	free(map);
	return (new_map);
}

void	change_space(char **map)
{
	int	i;
	int	j;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
				map[i][j] = '1';
			++j;
		}
		++i;
	}
}

void	parse_map(char *str, t_info *info)
{
	if (!str || !(*str))
		return ;
	if (valid_map(str))
		info->map = fill_map(str, info->map, &info->height);
	else
	{
		free(str);
		error_handler("Invalid Map\n", info);
	}
}
