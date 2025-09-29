/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymisbah <aymisbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:50:03 by aymisbah          #+#    #+#             */
/*   Updated: 2025/08/26 03:06:57 by aymisbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"




void initialize(t_game *game)
{
	game->tile_size = TILE_SIZE;
	game->player.walkSpeed = 5;
	game->player.turnSpeed = 0.05f;
	calc_w_h(game);
	init_textures(game); 
	player_pos(game);
}
