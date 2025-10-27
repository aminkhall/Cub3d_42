/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymisbah <aymisbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:50:03 by aymisbah          #+#    #+#             */
/*   Updated: 2025/10/27 12:54:57 by aymisbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	map_dimensions(t_game *game)
{
	int	max_width;
	int	height;
	int	width;

	height = -1;
	max_width = 0;
	while (game->info.map[++height])
	{
		width = ft_strlen(game->info.map[height]);
		if (width > max_width)
			max_width = width;
	}
	game->m_wd = max_width;
	game->m_ht = height;
}

void	rot_angle(t_game *game, int x, int y, char c)
{
	game->player.x = (x + 0.5f) * game->t_size;
	game->player.y = (y + 0.5f) * game->t_size;
	if (c == 'N')
		game->player.rotat_ang = -PI / 2;
	if (c == 'S')
		game->player.rotat_ang = PI / 2;
	if (c == 'E')
		game->player.rotat_ang = 0;
	if (c == 'W')
		game->player.rotat_ang = PI;
	game->info.map[y][x] = '0';
}

void	player_pos(t_game *game)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (game->info.map[y])
	{
		x = 0;
		while (game->info.map[y][x])
		{
			c = game->info.map[y][x];
			if (c != '1' && c != '0' && c != 'D')
			{
				rot_angle(game, x, y, c);
				return ;
			}
			x++;
		}
		y++;
	}
}

void	assign_path(t_game *game, char *path[9])
{
	path[0] = game->info.north;
	path[1] = game->info.south;
	path[2] = game->info.east;
	path[3] = game->info.west;
	path[4] = game->info.door;
	path[5] = game->info.anim[0];
	path[6] = game->info.anim[1];
	path[7] = game->info.anim[2];
	path[8] = game->info.anim[3];
}

void	initialize(t_game *game)
{
	game->t_size = TILE_SIZE;
	game->player.speed_w = 5;
	game->player.speed_t = 0.1f;
	game->fov = 60 * (PI / 180);
	game->last_x = -1;
	map_dimensions(game);
	init_textures(game);
	player_pos(game);
}
