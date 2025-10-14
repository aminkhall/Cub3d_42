/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:49:58 by aymisbah          #+#    #+#             */
/*   Updated: 2025/10/07 17:27:04 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void put_pixel(t_game *game, int x, int y, int color)
{
    if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
        return;
    char *dst = game->addr + (y * game->line_len + x * (game->bpp / 8));
    *(unsigned int *)dst = color;
}

int rgb_to_int(int r, int g, int b)
{
    return (r  << 16 | g  << 8 | b);
}

int get_tex_color(t_texture *tex, int x, int y)
{
    char *dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
    return *(unsigned int *)dst;
}

int is_wall(float x, float y, t_game *game)
{
    float padding = 0.1f; // in pixels or fraction of tile
    int mapX = (int)((x + padding) / game->tile_size);
    int mapY = (int)((y + padding) / game->tile_size);
    // if (mapX < 0 || mapX >= game->map_width || mapY < 0 || mapY >= game->map_height)
    //     return 1;
    char c = game->info.map[mapY][mapX];
    return (c == '1');
}

void update_player(t_game *game)
{
    t_player *p = &game->player;
    p->rotationAngle += p->turnDirection * p->turnSpeed;
    float moveStep = p->walkDirection * p->walkSpeed;
    float strafeStep = p->strafeDirection * p->walkSpeed;
    float newX = p->x + cos(p->rotationAngle) * moveStep + cos(p->rotationAngle + PI / 2) * strafeStep;
    float newY = p->y + sin(p->rotationAngle) * moveStep + sin(p->rotationAngle + PI / 2) * strafeStep;
    // if (game->player.y)
    if (!is_wall(newX + 5, game->player.y, game) &&
    !is_wall(newX - 5, game->player.y, game))
        p->x = newX;
    if (!is_wall(game->player.x, newY + 5, game) &&
    !is_wall(game->player.x, newY - 5, game))
        p->y = newY;
}


int handle_input(int key, t_game *game)
{
    if (key == KEY_ESC)
    {
        ft_clean(&game->info);
        exit(0);
    }
    if (key == KEY_W)
        game->player.walkDirection = +1;
    else if (key == KEY_S)
        game->player.walkDirection = -1;
    else if (key == KEY_A)
        game->player.strafeDirection = -1;
    else if (key == KEY_D)
        game->player.strafeDirection = +1;
    else if (key == KEY_LEFT)
        game->player.turnDirection = -1;
    else if (key == KEY_RIGHT)
        game->player.turnDirection = +1;
    return 0;
}

int release_input(int key, t_game *game)
{
    if (key == KEY_W || key == KEY_S)
        game->player.walkDirection = 0;
    else if (key == KEY_D || key == KEY_A)
        game->player.strafeDirection = 0;
    else if (key == KEY_LEFT || key == KEY_RIGHT)
        game->player.turnDirection = 0;
    return 0;
}
int check_wall(t_game *game,int mapX,int mapY)
{
    char cell = game->info.map[mapY][mapX];
    if (cell != '0') 
        return (1);
    return (0);
}
void check_sides(t_game *game,t_ray *ray)
{
    while (!check_wall(game,game->mapX,game->mapY))
    {
        if (game->sideDistX < game->sideDistY)
        {
            game->sideDistX += game->deltaDistX;
            game->mapX += game->stepX;
            if ((game->stepX > 0))
                ray->side = 'e';
            else
                ray->side = 'w';
        }
        else
        {
            game->sideDistY += game->deltaDistY;
            game->mapY += game->stepY;
            if ((game->stepY > 0))
                ray->side = 's';
            else
                ray->side = 'n';
        }
    }
}


void grid_distance(t_game *game,t_ray *ray,float ray_angle)
{
    if (cos(ray_angle) < 0)
        game->stepX = -1;
    else
        game->stepX = 1;

    if (sin(ray_angle) < 0)
        game->stepY = -1;
    else
        game->stepY = 1;
    if (game->stepX > 0)
        game->sideDistX = ((game->mapX + 1) * game->tile_size - game->player.x) * game->deltaDistX / game->tile_size;
    else
        game->sideDistX = (game->player.x - game->mapX * game->tile_size) * game->deltaDistX / game->tile_size;

    if (game->stepY > 0)
        game->sideDistY = ((game->mapY + 1) * game->tile_size - game->player.y) * game->deltaDistY / game->tile_size;
    else
        game->sideDistY = (game->player.y - game->mapY * game->tile_size) * game->deltaDistY / game->tile_size;
    check_sides(game,ray);
}
void hit_point(t_game *game,t_ray *ray,float ray_angle)
{
    float hitX, hitY;
    if (ray->side == 'e' || ray->side == 'w')
    {
        hitX = game->player.x + cos(ray_angle) * (game->sideDistX - game->deltaDistX);
        hitY = game->player.y + sin(ray_angle) * (game->sideDistX - game->deltaDistX);
    }
    else
    {
        hitX = game->player.x + cos(ray_angle) * (game->sideDistY - game->deltaDistY);
        hitY = game->player.y + sin(ray_angle) * (game->sideDistY - game->deltaDistY);
    }
    ray->x = hitX;
    ray->y = hitY;
    float relative_angle = ray_angle - game->player.rotationAngle;
    relative_angle = fmodf(relative_angle + PI, TWO_PI) - PI;
    ray->distance = sqrt((hitX - game->player.x)*(hitX - game->player.x) +
                         (hitY - game->player.y)*(hitY - game->player.y));
    ray->distance *= cos(relative_angle);
}

void render_ray(t_game *game, float ray_angle, int i)
{
    float relative_angle;
    t_ray *ray ;

    ray = &game->rays[i];
    game->mapX = (int)(game->player.x / game->tile_size);
    game->mapY = (int)(game->player.y / game->tile_size);
    game->deltaDistX = fabs(1 / cos(ray_angle)) * game->tile_size;
    game->deltaDistY = fabs(1 / sin(ray_angle)) * game->tile_size;
    grid_distance(game,ray,ray_angle);
    hit_point(game,ray,ray_angle);

}

void render_rays(t_game *game)
{
    float start_angle;
    float angle_step;
    float ray_angle;
    int i;

    start_angle = game->player.rotationAngle - (FOV_ANGLE / 2);
    angle_step = FOV_ANGLE / (NUM_RAYS );
    i = 0;
    while (i < NUM_RAYS)
    {
        ray_angle = start_angle + i * angle_step;
        render_ray(game, ray_angle, i);
        i++;
    }
}

// int choose_texture(t_game *game,t_texture **tex,t_ray *ray)
// {
//      float tex_x;
//     if (ray->side == 'n')
//         tex = &game->textures[0];
//     else if (ray->side == 's')
//         tex = &game->textures[1];
//     else if (ray->side == 'e')
//         tex = &game->textures[2];
//     else
//         tex = &game->textures[3];
//     if (ray->side == 'n' || ray->side == 's')
//         tex_x = fmodf(ray->x, game->tile_size) / game->tile_size * tex->width;
//     else
//         tex_x = fmodf(ray->y, game->tile_size) / game->tile_size * tex->width;
//     return (tex_x);
// }

// void draw(t_game *game,t_texture *tex,float tex_x,float wall_height)
// {
//     int top;
//     int bottom;
//     float t;
//     int tex_y;

//     top    = (int)(WINDOW_HEIGHT / 2 - wall_height / 2);
//     bottom = (int)(WINDOW_HEIGHT / 2 + wall_height / 2);
//     if (top < 0)
//          top = 0;
//     if (bottom > WINDOW_HEIGHT) 
//         bottom = WINDOW_HEIGHT;
//     while (game->screen_x0 < game->screen_x1) 
//     {
//         int y = top;
//         while (y < bottom) 
//         {
//             t = (float)(y - top) / (float)(bottom - top);
//             tex_y = (int)(t * tex->height);
//             if (tex_y < 0) 
//                 tex_y = 0;
//             if (tex_y >= tex->height) 
//                 tex_y = tex->height - 1;
//             put_pixel(game, game->screen_x0, y, get_tex_color(tex, (int)tex_x, tex_y));
//             y++;
//         }
//         game->screen_x0++;
//     }
// }

// void render_map(t_game *game, float wall_height, int i)
// {
//     t_ray *ray = &game->rays[i];
//     t_texture *tex;
//     float tex_x;

//     game->screen_x0 = i;
//     game->screen_x1 = i + 1;
//     // if (game->screen_x1 <= game->screen_x0) 
//     //     game->screen_x1 = game->screen_x0 + 1;
//     // if (game->screen_x0 < 0) 
//     //     game->screen_x0 = 0;
//     // if (game->screen_x1 > WINDOW_WIDTH) 
//     //     game->screen_x1 = WINDOW_WIDTH;
//     tex_x = choose_texture(game, &tex,ray);
//     if (tex_x < 0) 
//         tex_x += tex->width;
//     draw(game,tex,tex_x,wall_height);
// }
void render_map(t_game *game, float wall_height, int i)
{
    t_ray *ray = &game->rays[i];
    t_texture *tex;
    int screen_x0;
    int screen_x1;
    int top;
    int bottom;
    
    screen_x0 = (i * WINDOW_WIDTH) / NUM_RAYS;
    screen_x1 = ((i + 1) * WINDOW_WIDTH) / NUM_RAYS;
    if (screen_x1 <= screen_x0) 
        screen_x1 = screen_x0 + 1;
    if (screen_x0 < 0) 
        screen_x0 = 0;
    if (screen_x1 > WINDOW_WIDTH) 
        screen_x1 = WINDOW_WIDTH;

    top    = (int)(WINDOW_HEIGHT / 2 - wall_height / 2);
    bottom = (int)(WINDOW_HEIGHT / 2 + wall_height / 2);
    if (top < 0)
         top = 0;
    if (bottom > WINDOW_HEIGHT) 
        bottom = WINDOW_HEIGHT;
    float tex_x;
    if (ray->side == 'n')
        tex = &game->textures[0];
    else if (ray->side == 's')
        tex = &game->textures[1];
    else if (ray->side == 'e')
        tex = &game->textures[2];
    else
        tex = &game->textures[3];
    if (ray->side == 'n' || ray->side == 's')
        tex_x = fmodf(ray->x, game->tile_size) / game->tile_size * tex->width;
    else
        tex_x = fmodf(ray->y, game->tile_size) / game->tile_size * tex->width;

    if (tex_x < 0) 
        tex_x += tex->width;
    float tex_step = (float)tex->height / wall_height;
    float tex_pos = (top - WINDOW_HEIGHT / 2 + wall_height / 2) * tex_step;
    int x = screen_x0;
    while (x < screen_x1) 
    {
        int y = top;
        float tex_y_pos = tex_pos;

        while (y < bottom) 
        {
            int tex_y = (int)tex_y_pos;
            if (tex_y < 0) tex_y = 0;
            if (tex_y >= tex->height) tex_y = tex->height - 1;

            int color = get_tex_color(tex, (int)tex_x, tex_y);
            put_pixel(game, x, y, color);

            tex_y_pos += tex_step;
            y++;
        }
        x++;
    }
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


int game_loop(t_game *game)
{
    game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    game->addr = mlx_get_data_addr(game->img, &game->bpp, &game->line_len, &game->endian);
    render_rays(game);
    map_3d(game);
    // render_minimap(game);
    update_player(game);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    mlx_destroy_image(game->mlx, game->img);
    return 0;
}

void calc_w_h(t_game *game)
{
    int height;
    int width;

    height = 0;
    while (game->info.map[height])
    {
        width = ft_strlen(game->info.map[height]);
        if (width > game->map_width) 
            game->map_width = width;
        height++;
    }
    game->map_height = height;
}

void init_textures(t_game *game)
{
    char *path[4] ;
    int i = 0;
    
    path[0] = game->info.north; 
    path[1] = game->info.south; 
    path[2] = game->info.east; 
    path[3] = game->info.west; 
    while (i < 4)
    {
        game->textures[i].img = mlx_xpm_file_to_image(game->mlx, path[i],
            &game->textures[i].width, &game->textures[i].height);

        if (!game->textures[i].img)
        {
            printf("img not found %s\n", path[i]);
            exit(1);
        }
        game->textures[i].addr = mlx_get_data_addr(game->textures[i].img,
            &game->textures[i].bpp, &game->textures[i].line_len,
            &game->textures[i].endian);
        i++;
    }
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




int main(int ac, char **av)
{
    t_game game;
    
    ft_memset(&game, 0, sizeof(t_game));
    if (ac != 2)
        return (1);
    if (!valid_filename(av[1]))
        return (1);
    if (!parsing(av[1], &game.info))
        return (1);
        
    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub");
    initialize(&game);
    mlx_hook(game.win, 2, 1L<<0, handle_input, &game);
    mlx_hook(game.win, 3, 1L<<1, release_input, &game);
    mlx_loop_hook(game.mlx, game_loop, &game);
    mlx_loop(game.mlx);
    return 0;
}