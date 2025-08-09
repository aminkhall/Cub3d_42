/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 20:11:03 by mkhallou          #+#    #+#             */
/*   Updated: 2025/08/09 19:36:18 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	is_map(char *str)
{
	while (*str && *str == ' ')
		++str;
	if (*str == '1')
		return (1);
	return (0);
}

int	count_direction(char **str)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == 'N' || str[i][j] == 'E' || str[i][j] == 'S'
				|| str[i][j] == 'W')
				++count;
			++j;
		}
		if (count > 1)
			return (puts("players > 1"), count);
		++i;
	}
	return (count);
}

int	valid_map(char *str)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	if (!len)
		return (0);
	i = 0;
	while (str[i] && str[i] == ' ')
		++i;
	while (len && str[len - 1] == ' ')
		--len;
	if (str[i] != '1' && str[len] != '1')
		return (puts("error"), 0);
	while (str[i])
	{
		if (str[i] != '1' && str[i] != '0' && str[i] != 'N' && str[i] != 'E'
			&& str[i] != 'S' && str[i] != 'W' && str[i] != ' ')
			return (0);
		++i;
	}
	return (1);
}

int	check_map(t_info *info, int height)
{
	int	i;

	i = 0;
	while (info->map[height][i])
	{
		if (info->map[height][i] != '1' && info->map[height][i] != ' ')
			return (0);
		++i;
	}
	return (1);
}

char	**fill_map(char *str, char **map, int *height)
{
	char	**new_map;
	int		i;

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

void	parse_map(char *str, t_info *info)
{
	if (valid_map(str))
		info->map = fill_map(str, info->map, &info->height);
	else
	{
		printf("Invalid Map\n");
		ft_clean(info);
		exit(1);
	}
}
