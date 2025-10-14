/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 20:13:52 by mkhallou          #+#    #+#             */
/*   Updated: 2025/10/07 17:25:53 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	count_comma(char *str)
{
	int	i;
	int	count;

	if (!str)
		return (0);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			++count;
		++i;
	}
	if (count == 2)
		return (1);
	return (0);
}

int	is_color(char *str)
{
	char	**line;

	if (!str || !(*str))
		return (0);
	line = ft_split(str, ' ');
	if (!line)
		return (0);
	if (!ft_strncmp(line[0], "F", 2))
		return (ft_free(line), 1);
	else if (!ft_strncmp(line[0], "C", 2))
		return (ft_free(line), 1);
	return (ft_free(line), 0);
}

int	get_color(char *str, int rgb[3])
{
	char	**color;

	if (!str || !(*str) || !count_comma(str))
		return (-1);
	color = ft_split(str, ',');
	if (!color || !color[0] || !color[1] || !color[2] || color[3])
		return (ft_free(color), -1);
	rgb[0] = ft_atoi(color[0]);
	rgb[1] = ft_atoi(color[1]);
	rgb[2] = ft_atoi(color[2]);
	ft_free(color);
	if (rgb[0] < 0 || rgb[1] < 0 || rgb[2] < 0)
		return (-1);
	return (0);
}

void	parse_color(char *str, t_info *info)
{
	char	**line;

	if (!str || !(*str))
		return ;
	line = ft_split(str, ' ');
	if (!line || !line[0] || !line[1] || line[2])
		(free(str), ft_free(line), error_handler("Color Invalid", info));
	if (!ft_strncmp(line[0], "F", 2))
	{
		++info->n_cfloor;
		if (get_color(line[1], info->cfloor) < 0)
			(free(str), ft_free(line), error_handler("Invalid Floor Values",
					info));
	}
	else if (!ft_strncmp(line[0], "C", 2))
	{
		++info->n_cceiling;
		if (get_color(line[1], info->cceiling) < 0)
			(free(str), ft_free(line), error_handler("Invalid Ceiling  Values",
					info));
	}
	ft_free(line);
}
