/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 20:11:06 by mkhallou          #+#    #+#             */
/*   Updated: 2025/09/29 19:22:35 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	full_map(t_info *info)
{
	if (!check_map(info, 0) || !check_map(info, info->height - 1)
		|| count_direction(info->map, &info->direc) != 1
		|| info->n_cceiling != 1 || info->n_cfloor != 1 || !info->east
		|| !info->north || !info->south || !info->west
		|| !check_space(info->map, info->direc))
		error_handler("Invalid input", info);
	close(info->fd);
	change_space(info->map);
	info->door = ft_strdup("images/door.xpm");
	info->anim[0] = ft_strdup("images/anim0.xpm");
	info->anim[1] = ft_strdup("images/anim1.xpm");
	info->anim[2] = ft_strdup("images/anim2.xpm");
	info->anim[3] = ft_strdup("images/anim3.xpm");
}

int	parsing(char *filename, t_info *info)
{
	char	*line;

	line = NULL;
	info->fd = open(filename, O_RDONLY);
	if (info->fd < 0)
		return (printf("File dosen't found\n"), 0);
	while (1)
	{
		line = get_next_line(info->fd);
		if (!line)
			break ;
		if (!info->map && *line && is_texter(line))
			parse_texter(line, info);
		else if (!info->map && *line && is_color(line))
			parse_color(line, info);
		else if (*line && is_map(line))
			parse_map(line, info);
		else if ((!(*line) && (info->map)))
			(free(line), error_handler("Invalid input", info));
		else if (*line)
			(free(line), error_handler("Invalid input", info));
		free(line);
	}
	full_map(info);
	return (1);
}

int	valid_filename(char *str)
{
	int	i;

	if (!str || !(*str))
		return (0);
	i = ft_strlen(str);
	if (!i)
		return (0);
	while (i && str[i] != '.')
		--i;
	if (!ft_strncmp(str + i, ".cub", 5))
		return (1);
	return (0);
}
