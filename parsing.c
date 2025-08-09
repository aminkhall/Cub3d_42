/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 20:11:06 by mkhallou          #+#    #+#             */
/*   Updated: 2025/08/09 20:27:38 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	parsing(char *filename, t_info *info)
{
	char	*line;

	info->fd = open(filename, O_RDONLY);
	if (info->fd < 0)
		return (puts("File dosen't found"), 0);
	while ((line = get_next_line(info->fd)))
	{
		if (!info->map && *line && is_texter(line))
			parse_texter(line, info);
		else if (!info->map && *line && is_color(line))
			parse_color(line, info);
		else if (*line && is_map(line))
			parse_map(line, info);
		else if (*line)
			return (close(info->fd), free(line), ft_clean(info), 0);
		free(line);
	}
	close(info->fd);
	if (!check_map(info, 0) || !check_map(info, info->height - 1)
		|| count_direction(info->map) > 1 || info->n_cceiling != 1
		|| info->n_cfloor != 1 || !info->east || !info->north
        || !info->south || !info->west)
		return (puts("invalid input"), ft_clean(info), 0);
	return (1);
}

int	valid_filename(char *str)
{
	int	i;

	if (!str || !(*str))
		return (0);
	i = 0;
	while (str[i] && str[i] != '.')
		++i;
	if (!ft_strncmp(str + i, ".cub", 5))
		return (1);
	return (0);
}

void	ff(void)
{
	system("leaks cub");
}

int	main(int ac, char **av)
{
	t_info	info;
	int		i;

	// atexit(ff);
	ft_memset(&info, 0, sizeof(t_info));
	if (ac != 2)
		return (1);
	if (!valid_filename(av[1]))
		return (1);
	if (!parsing(av[1], &info))
		return (1);
	printf("%s\n%s\n%s\n%s\n", info.east, info.north, info.south, info.west);
	printf("%d\n%d\n%d\n", info.cfloor[0], info.cfloor[1], info.cfloor[2]);
	printf("%d\n%d\n%d\n", info.cceiling[0], info.cceiling[1],
		info.cceiling[2]);
	i = 0;
	while (info.map[i])
	{
		printf("%s\n", info.map[i]);
		++i;
	}
	ft_clean(&info);
	return (0);
}
