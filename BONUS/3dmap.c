#include "cub3d_bonus.h"


void coor_calculation(t_game *game,t_texture *tex,float wall_height)
{
    tex->top    = (int)(WINDOW_HEIGHT / 2 - wall_height / 2);
    tex->bottom = (int)(WINDOW_HEIGHT / 2 + wall_height / 2);
    if ( tex->top < 0)
          tex->top = 0;
    if ( tex->bottom > WINDOW_HEIGHT) 
         tex->bottom = WINDOW_HEIGHT;
    tex->tex_step = (float)tex->height / wall_height;
    tex->tex_pos = ( tex->top - WINDOW_HEIGHT / 2 + wall_height / 2) * tex->tex_step;
}

void draw(t_game *game,t_texture *tex,float tex_x,float wall_height)
{
    int x;
    int y;
    int tex_y;
    int color;
    coor_calculation(game,tex,wall_height);
    x = game->s_col;
    while (x < game->e_col) 
    {
        y = tex->top;
        while (y < tex->bottom) 
        {
            tex_y = (int)tex->tex_pos;
            if (tex_y < 0) 
                tex_y = 0;
            if (tex_y >= tex->height) 
                tex_y = tex->height - 1;
            color = get_tex_color(tex, (int )(tex_x), tex_y);
            put_pixel(game, x, y, color);
            tex->tex_pos += tex->tex_step;
            y++;
        }
        x++;
    }
}

void	choose_texture(t_game *game, t_ray *ray, t_texture **tex, float *tex_x)
{
    if (ray->door)
        *tex = &game->textures[4];
    else if (ray->side == 'n')
        *tex = &game->textures[0];
    else if (ray->side == 's')
        *tex = &game->textures[1];
    else if (ray->side == 'e')
        *tex = &game->textures[2];
    else
        *tex = &game->textures[3];

    if (ray->side == 'n' || ray->side == 's')
        *tex_x = fmodf(ray->x, game->tile_size) / game->tile_size * (*tex)->width;
    else
        *tex_x = fmodf(ray->y, game->tile_size) / game->tile_size * (*tex)->width;

    if (*tex_x < 0)
        *tex_x += (*tex)->width;
}

void render_map(t_game *game, float wall_height, int i)
{
    t_ray *ray = &game->rays[i];
    t_texture *tex;
    float tex_x;

    game->s_col = (i * WINDOW_WIDTH) / NUM_RAYS;
    game->e_col = ((i + 1) * WINDOW_WIDTH) / NUM_RAYS;
    if (game->e_col <= game->s_col) 
        game->e_col = game->s_col + 1;
    if (game->s_col < 0) 
        game->s_col = 0;
    if (game->e_col > WINDOW_WIDTH) 
        game->e_col = WINDOW_WIDTH;
    choose_texture(game, ray, &tex, &tex_x);
    if (tex_x < 0) 
        tex_x += tex->width; 
    draw(game,tex,tex_x,wall_height);
    
}



void c_f_colors(t_game *game)
{
    int c_color;
    int f_color;
    int x;
    int y;

    c_color = rgb_to_int(game->info.cceiling[0], game->info.cceiling[1], game->info.cceiling[2]);
    f_color = rgb_to_int(game->info.cfloor[0],   game->info.cfloor[1],   game->info.cfloor[2]);
    x = 0;
    while (x < WINDOW_WIDTH) 
    {
        y = 0;
        while (y < WINDOW_HEIGHT) 
        {
            if (y < WINDOW_HEIGHT / 2)
                put_pixel(game, x, y, c_color);
            else 
                put_pixel(game, x, y,  f_color);
            y++;
        }
        x++;
    }
    
}

void map_3d(t_game *game)
{
    int i;
    float proj_dist;
    float dist;
    float wall_height;

    c_f_colors(game);
    proj_dist = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
    i = 0;
    while (i < NUM_RAYS) 
    {
        dist = game->rays[i].distance;
        if (dist < 0) 
            dist = 0;
        wall_height = (game->tile_size / dist) * proj_dist;
        if (wall_height < 1) 
            wall_height = 1;
        render_map(game, wall_height, i);
        i++;
    }
}