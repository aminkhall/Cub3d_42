/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texter_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 20:13:55 by mkhallou          #+#    #+#             */
/*   Updated: 2025/10/25 14:30:44 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	is_texter(char *str)
{
	char	**line;

	if (!str || !(*str))
		return (0);
	line = ft_split(str, ' ');
	if (!ft_strncmp(line[0], "NO", 3))
		return (ft_free(line), 1);
	else if (!ft_strncmp(line[0], "SO", 3))
		return (ft_free(line), 1);
	else if (!ft_strncmp(line[0], "WE", 3))
		return (ft_free(line), 1);
	else if (!ft_strncmp(line[0], "EA", 3))
		return (ft_free(line), 1);
	return (ft_free(line), 0);
}

int	valid_texter(char *str)
{
	int	i;

	if (!str || !(*str))
		return (0);
	i = ft_strlen(str);
	if (!i)
		return (0);
	while (i && str[i] != '.')
		--i;
	if (!ft_strncmp(str + i, ".xpm", 5))
		return (1);
	return (0);
}

void	parse_texter(char *str, t_info *info)
{
	char	**line;

	line = ft_split(str, ' ');
	if (!line || !line[0] || !line[1] || line[2] || !valid_texter(line[1]))
		(free(str), ft_free(line), error_handler("*   Invalid Input   *",
				info));
	if (!ft_strncmp(line[0], "NO", 3) && !info->north)
		info->north = ft_strdup(line[1]);
	else if (!ft_strncmp(line[0], "SO", 3) && !info->south)
		info->south = ft_strdup(line[1]);
	else if (!ft_strncmp(line[0], "WE", 3) && !info->west)
		info->west = ft_strdup(line[1]);
	else if (!ft_strncmp(line[0], "EA", 3) && !info->east)
		info->east = ft_strdup(line[1]);
	else
		(free(str), ft_free(line), error_handler("*   Invalid Input   *",
				info));
	ft_free(line);
	return ;
}
