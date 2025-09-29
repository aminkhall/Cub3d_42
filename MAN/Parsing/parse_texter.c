/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 20:13:55 by mkhallou          #+#    #+#             */
/*   Updated: 2025/09/29 19:08:38 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

int	dup_texter(char *texter, t_info *info)
{
	int	count;

	count = 0;
	if (!ft_strncmp(texter, info->east, ft_strlen(info->east)))
		++count;
	if (!ft_strncmp(texter, info->north, ft_strlen(info->north)))
		++count;
	if (!ft_strncmp(texter, info->south, ft_strlen(info->south)))
		++count;
	if (!ft_strncmp(texter, info->west, ft_strlen(info->west)))
		++count;
	return (count == 1);
}

int	check_texter(t_info *info)
{
	if (!dup_texter(info->east, info))
		return (0);
	else if (!dup_texter(info->north, info))
		return (0);
	else if (!dup_texter(info->south, info))
		return (0);
	else if (!dup_texter(info->west, info))
		return (0);
	return (1);
}

void	parse_texter(char *str, t_info *info)
{
	char	**line;

	line = ft_split(str, ' ');
	if (!line || !line[0] || !line[1] || line[2] || !valid_texter(line[1]))
		(ft_free(line), error_handler("Invalid input", info));
	if (!ft_strncmp(line[0], "NO", 3) && !info->north)
		info->north = ft_strdup(line[1]);
	else if (!ft_strncmp(line[0], "SO", 3) && !info->south)
		info->south = ft_strdup(line[1]);
	else if (!ft_strncmp(line[0], "WE", 3) && !info->west)
		info->west = ft_strdup(line[1]);
	else if (!ft_strncmp(line[0], "EA", 3) && !info->east)
		info->east = ft_strdup(line[1]);
	else
		(ft_free(line), error_handler("Dup Texter", info));
	ft_free(line);
	return ;
}
