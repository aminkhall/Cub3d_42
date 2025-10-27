/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_mouse_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:22:55 by mkhallou          #+#    #+#             */
/*   Updated: 2025/10/19 15:43:49 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	player_inside_door(t_game *game, t_player *p, int door_map_x,
		int door_map_y)
{
	int	player_map_x;
	int	player_map_y;

	player_map_x = (int)(p->x / game->t_size);
	player_map_y = (int)(p->y / game->t_size);
	if (player_map_x == door_map_x && player_map_y == door_map_y)
		return (1);
	return (0);
}

void	open_door(t_game *game)
{
	t_player	*p;
	float		check_x;
	float		check_y;
	int			map_x;
	int			map_y;

	p = &game->player;
	check_x = p->x + cos(p->rotat_ang) * (game->t_size);
	check_y = p->y + sin(p->rotat_ang) * (game->t_size);
	map_x = (int)(check_x / game->t_size);
	map_y = (int)(check_y / game->t_size);
	if (map_x < 0 || map_x >= game->m_wd || map_y < 0 || map_y >= game->m_ht)
		return ;
	if (!player_inside_door(game, p, map_x, map_y))
	{
		if (game->info.map[map_y][map_x] == 'D')
			game->info.map[map_y][map_x] = 'O';
		else if (game->info.map[map_y][map_x] == 'O')
			game->info.map[map_y][map_x] = 'D';
	}
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
			game->player.trn_dr = -1;
		else if (dx > 0)
			game->player.trn_dr = 1;
		else
			game->player.trn_dr = 0;
		game->last_x = x;
	}
	else
		game->player.trn_dr = 0;
	return (0);
}
