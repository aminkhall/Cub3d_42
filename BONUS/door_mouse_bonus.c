/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_mouse_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:22:55 by mkhallou          #+#    #+#             */
/*   Updated: 2025/10/09 19:29:59 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	open_door(t_game *game)
{
	t_player	*p;
	float		check_x;
	float		check_y;
	int			map_x;
	int			map_y;

	p = &game->player;
	check_x = p->x + cos(p->rotationAngle) * (game->tile_size);
	check_y = p->y + sin(p->rotationAngle) * (game->tile_size);
	map_x = (int)(check_x / game->tile_size);
	map_y = (int)(check_y / game->tile_size);
	if (map_x < 0 || map_x >= game->map_width || map_y < 0
		|| map_y >= game->map_height)
		return ;
	if (game->info.map[map_y][map_x] == 'D')
		game->info.map[map_y][map_x] = 'O';
	else if (game->info.map[map_y][map_x] == 'O')
		game->info.map[map_y][map_x] = 'D';
}

int	mouse_hook(int x, int y, t_game *game)
{
	int	dx;

	if (game->last_x == -1)
	{
		game->last_x = x;
		return (0);
	}
	if (x >= 0 && x <= WINDOW_WIDTH && y >= 0 && y <= WINDOW_HEIGHT)
	{
		dx = x - game->last_x;
		if (dx < 0)
			game->player.turnDirection = -1;
		else if (dx > 0)
			game->player.turnDirection = 1;
		else
			game->player.turnDirection = 0;
		game->last_x = x;
	}
	else
		game->player.turnDirection = 0;
	return (0);
}
