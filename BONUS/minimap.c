#include "cub3d_bonus.h"

void draw_map2d(t_game *game, int x, int y, int size, int color)
{
    int i;
    int j;
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
            if (x * x + y * y <= radius * radius)
                put_pixel(game, cx + x, cy + y, color);
        }
    }
}

int ft_max_len(char **map)
{
    int i;
    int len;
    int max_len;

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

void map_2d(t_game *game)
{
    int scaleX = WINDOW_WIDTH / 2;
    int scaleY = WINDOW_HEIGHT / 2;
    int min_w = ft_max_len(game->info.map);
    int min_h = game->info.height;
    int scale_size = (scaleX / min_w < scaleY / min_h) ? scaleX / min_w : scaleY / min_h;
    int color;
    int row = -1; 
    while (++row < game->info.height)
    {
        int col = -1;
        while (++col < ft_strlen(game->info.map[row]))
        {
            char cell = game->info.map[row][col];
            if (cell == '1')
                color = BLACK;
            else if (cell == '0' || cell == 'O')
                color = WHITE;
            else if (cell == 'D')
                color = YELLOW;
            draw_map2d(game, col * scale_size,
                row * scale_size, scale_size, color);
        }
    }
    float player_tile_x = game->player.x / TILE_SIZE;
    float player_tile_y = game->player.y / TILE_SIZE;
    int player_x = (int)(player_tile_x * scale_size);
    int player_y = (int)(player_tile_y * scale_size);
    draw_circle(game, player_x, player_y, scale_size / 2, RED);
}

