/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:50:03 by aymisbah          #+#    #+#             */
/*   Updated: 2025/09/29 19:28:20 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"



void	wall_free(t_game *game)
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
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
                puts("hna");
				game->player.x = x * game->tile_size + game->tile_size / 2;
				game->player.y = y * game->tile_size + game->tile_size / 2;
                printf("x : %f y: %f\n",game->player.x,game->player.y);
				if (c == 'N')
					game->player.rotationAngle = 3 * PI / 2;
				else if (c == 'S')
					game->player.rotationAngle = PI / 2;
				else if (c == 'E')
					game->player.rotationAngle = 0;
				else if (c == 'W')
					game->player.rotationAngle = PI;
				game->info.map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}





// void initialize(t_game *game)
// {
//     game->tile_size = TILE_SIZE;

//     wall_free(game);
//     game->player.width = 1;
//     game->player.height = 1;
//     game->player.turnDirection = 0;
//     game->player.walkDirection = 0;
//     game->player.strafeDirection = 0;
//     game->player.rotationAngle = PI / 2;
//     game->player.walkSpeed = 1;
//     game->player.turnSpeed = 1 * (PI / 180);
// }