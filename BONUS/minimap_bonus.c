/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymisbah <aymisbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:23:57 by mkhallou          #+#    #+#             */
/*   Updated: 2025/10/18 16:55:36 by aymisbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_map2d(t_game *game, t_rect *rect)
{
	int	i;
	int	j;

	i = rect->y;
	while (i < rect->y + rect->height)
	{
		j = rect->x;
		while (j < rect->x + rect->width)
		{
			put_pixel(game, j, i, rect->color);
			++j;
		}
		++i;
	}
}

void	cell_color(t_game *game, t_rect *rect, char cell)
{
	if (cell == '1')
		rect->color = BLACK;
	else if (cell == '0' || cell == 'O')
		rect->color = WHITE;
	else if (cell == 'D')
		rect->color = YELLOW;
	draw_map2d(game, rect);
}

void	draw_circle(t_game *game, t_rect rect)
{
	int	px;
	int	py;
	int	radius;
	int	x;
	int	y;

	px = (int)((game->player.x / TILE_SIZE) * rect.width);
	py = (int)((game->player.y / TILE_SIZE) * rect.height);
	radius = (int)(rect.width * 2.5);
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				put_pixel(game, px + x, py + y, RED);
			++x;
		}
		++y;
	}
}

int	ft_max_len(char **map)
{
	int	i;
	int	len;
	int	max_len;

	i = -1;
	max_len = 0;
	while (map[++i])
	{
		len = ft_strlen(map[i]);
		if (max_len < len)
			max_len = len;
	}
	return (max_len);
}

void	map_2d(t_game *game)
{
	t_rect	rect;
	int		col;
	int		row;
	char	cell;

	rect.width = (float)WINDOW_WIDTH / ft_max_len(game->info.map) / 6;
	rect.height = (float)WINDOW_HEIGHT / game->info.height / 6;
	col = -1;
	while (++col < game->info.height)
	{
		row = -1;
		while (++row < ft_strlen(game->info.map[col]))
		{
			cell = game->info.map[col][row];
			rect.x = (int)(row * rect.width);
			rect.y = (int)(col * rect.height);
			cell_color(game, &rect, cell);
		}
	}
	draw_circle(game, rect);
}
