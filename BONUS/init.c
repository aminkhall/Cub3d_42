/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:50:03 by aymisbah          #+#    #+#             */
/*   Updated: 2025/10/09 19:27:26 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
void map_dimensions(t_game *game)
{
    int max_width;
    int height;
    int width;

    height = 0;
    max_width = 0;
    while (game->info.map[height])
    {
        width = ft_strlen(game->info.map[height]);
        if (width > max_width) max_width = width;
        height++;
    }
    game->map_width = max_width;
    game->map_height = height;
}

void player_pos(t_game *game)
{
    int y;
    int x;

    y = 0;
    while (game->info.map[y]) 
    {
        x = 0;
        while (game->info.map[y][x]) 
        {
            char c = game->info.map[y][x];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W') 
            {
                game->player.x = (x + 0.5f) * game->tile_size;
                game->player.y = (y + 0.5f) * game->tile_size;
                if (c == 'N') 
                    game->player.rotationAngle = -PI / 2;
                if (c == 'S') 
                    game->player.rotationAngle =  PI / 2;
                if (c == 'E') 
                    game->player.rotationAngle = 0;
                if (c == 'W') 
                    game->player.rotationAngle = PI;
                game->info.map[y][x] = '0';
                return ;
            }
            x++;
        }
        y++;
    }
}
void init_textures(t_game *game)
{
    char *path[9] ;
    int i = 0;
    
    path[0] = game->info.north; 
    path[1] = game->info.south; 
    path[2] = game->info.east; 
    path[3] = game->info.west;
    path[4] = game->info.door;
    path[5] = game->info.anim[0];
    path[6] = game->info.anim[1];
    path[7] = game->info.anim[2];
    path[8] = game->info.anim[3];
    while (i < 9)
    {
        game->textures[i].img = mlx_xpm_file_to_image(game->mlx, path[i],
            &game->textures[i].width, &game->textures[i].height);
        if (!game->textures[i].img)
        {
            printf("Error: Failed to load texture %s\n", path[i]);
            exit(1);
        }
        game->textures[i].addr = mlx_get_data_addr(game->textures[i].img,
            &game->textures[i].bpp, &game->textures[i].line_len,
            &game->textures[i].endian);
        i++;
    }
}

void initialize(t_game *game)
{
    game->tile_size = TILE_SIZE;
    game->player.walkSpeed = 5;
    game->player.turnSpeed = 0.1f;
    game->last_x = -1;
    
    map_dimensions(game);
    init_textures(game); 
    player_pos(game);
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