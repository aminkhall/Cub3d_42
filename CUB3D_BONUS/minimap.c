#include "cub3d_bonus.h"

void draw_map2d(t_game *game, int x, int y, int color)
{
    int i;
    int j;
    int size = (int)(TILE_SIZE * MINIMAP_SCALE);
    i = -1;
    while (++i < size)
    {
        j = -1;
        while (++j < size)
            put_pixel(game, x + j, y + i, color);
    }
}

void draw_circle(t_game *game, int cx, int cy, int radius, int color)
{
    for (int y = -radius; y <= radius; y++)
    {
        for (int x = -radius; x <= radius; x++)
        {
            if (x * x + y * y <= radius * radius) // inside circle
                put_pixel(game, cx + x, cy + y, color);
        }
    }
}

void map_2d(t_game *game)
{
    int offset_x = 10; 
    int offset_y = 10;
    int scale_size = (int)(TILE_SIZE * MINIMAP_SCALE);
    
    for (int row = 0; row < game->info.height; row++)
    {
        for (int col = 0; game->info.map[row][col]; col++)
        {
            int color;
            if (game->info.map[row][col] == '1')
                color = BLACK;
            else if (game->info.map[row][col] == '0')
                color = WHITE;
            draw_map2d(game,
                offset_x + col * scale_size,
                offset_y + row * scale_size,
                color);
        }
    }
    float player_tile_x = game->player.x / TILE_SIZE;
    float player_tile_y = game->player.y / TILE_SIZE;
    int player_x = offset_x + (int)(player_tile_x * scale_size);
    int player_y = offset_y + (int)(player_tile_y * scale_size);
    draw_circle(game, player_x, player_y, 3, RED); // red circle
}

