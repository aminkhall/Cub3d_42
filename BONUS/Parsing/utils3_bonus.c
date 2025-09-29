/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:13:14 by mkhallou          #+#    #+#             */
/*   Updated: 2025/09/29 19:15:19 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	count_direction(char **str, char *dirc)
{
	int		count;
	int		i;
	int		j;
	char	c;

	if (!str || !(*str))
		return (0);
	count = 0;
	i = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			c = str[i][j];
			if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
			{
				*dirc = c;
				++count;
			}
		}
	}
	return (count);
}

int	check_map(t_info *info, int height)
{
	int	i;

	if (!info->map)
		return (0);
	i = 0;
	while (info->map[height][i])
	{
		if (info->map[height][i] != '1' && info->map[height][i] != ' ')
			return (0);
		++i;
	}
	return (1);
}

int	check_space(char **map, char dirc)
{
	int	i;
	int	j;

	if (!map)
		return (0);
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '0' || map[i][j] == dirc)
			{
				if (ft_strlen(map[i - 1]) >= j && map[i - 1][j] == ' ')
					return (0);
				if (ft_strlen(map[i + 1]) >= j && map[i + 1][j] == ' ')
					return (0);
				if (ft_strlen(map[i - 1]) <= j || ft_strlen(map[i + 1]) <= j)
					return (0);
				if (map[i][j + 1] == ' ' || map[i][j - 1] == ' ')
					return (0);
			}
		}
	}
	return (1);
}
