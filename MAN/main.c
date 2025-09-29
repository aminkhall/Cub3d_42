/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymisbah <aymisbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:49:58 by aymisbah          #+#    #+#             */
/*   Updated: 2025/08/29 20:56:22 by aymisbah         ###   ########.fr       */
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
        exit(0);
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

void ray_angles(t_game *game,t_ray *ray,float ray_angle)
{
    float distX;
    float distY;
    float newX;
    float newY;
    float step_size;

    step_size = 0.2f;
    while (1)
    {
        distX = cos(ray_angle) * step_size;
        distY = sin(ray_angle) * step_size;
        newX = ray->x + distX;
        newY = ray->y + distY;
        if (is_wall(newX, ray->y, game))
        {
            ray->x = newX;
            if (cos(ray_angle) > 0)
                ray->side = 'e';
            else
                ray->side = 'w';
            break ;
        }
        if (is_wall(ray->x, newY, game))
        {
            ray->y = newY;
            if (sin(ray_angle) > 0)
                ray->side = 's';
            else
                ray->side = 'n';   
            break ;
        }
        ray->x = newX;
        ray->y = newY;
    }
}


void render_ray(t_game *game, float ray_angle, int id)
{
    t_ray *ray = &game->rays[id];
    ray->x = game->player.x;
    ray->y = game->player.y;

    ray_angle = fmod(ray_angle, TWO_PI);
    ray_angles(game,ray,ray_angle);
    ray->dx = ray->x - game->player.x;
    ray->dy = ray->y - game->player.y;
    // fisheye correction
    float relative_angle = ray_angle - game->player.rotationAngle;
    ray->distance = sqrt(ray->dx * ray->dx + ray->dy * ray->dy);
    ray->distance *= cos(relative_angle);
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

int choose_texture(t_game *game,t_texture **tex,t_ray *ray)
{
    float tex_x;
    if (ray->side == 'n') 
    {
        *tex = &game->textures[0];
        tex_x = fmodf(ray->x, game->tile_size) / game->tile_size * (*tex)->width;
    } 
    else if (ray->side == 's') 
    {
        *tex = &game->textures[1];
        tex_x = fmodf(ray->x, game->tile_size) / game->tile_size * (*tex)->width;
    } 
    else if (ray->side == 'e') 
    {
        *tex = &game->textures[2];
        tex_x = fmodf(ray->y, game->tile_size) / game->tile_size * (*tex)->width;
    } 
    else
    {
        *tex = &game->textures[3]; 
        tex_x = fmodf(ray->y, game->tile_size) / game->tile_size * (*tex)->width;
    }
    return (tex_x);
}

void draw(t_game *game,t_texture *tex,float tex_x,float wall_height)
{
    int top;
    int bottom;
    float t;
    int tex_y;

    top    = (int)(WINDOW_HEIGHT / 2 - wall_height / 2);
    bottom = (int)(WINDOW_HEIGHT / 2 + wall_height / 2);
    if (top < 0)
         top = 0;
    if (bottom > WINDOW_HEIGHT) 
        bottom = WINDOW_HEIGHT;
    while (game->screen_x0 < game->screen_x1) 
    {
        int y = top;
        while (y < bottom) 
        {
            t = (float)(y - top) / (float)(bottom - top);
            tex_y = (int)(t * tex->height);
            if (tex_y < 0) 
                tex_y = 0;
            if (tex_y >= tex->height) 
                tex_y = tex->height - 1;
            put_pixel(game, game->screen_x0, y, get_tex_color(tex, (int)tex_x, tex_y));
            y++;
        }
        game->screen_x0++;
    }
}

void render_map(t_game *game, float wall_height, int i)
{
    t_ray *ray = &game->rays[i];
    t_texture *tex;
    float tex_x;

    game->screen_x0 = i;
    game->screen_x1 = i + 1;
    // if (game->screen_x1 <= game->screen_x0) 
    //     game->screen_x1 = game->screen_x0 + 1;
    // if (game->screen_x0 < 0) 
    //     game->screen_x0 = 0;
    // if (game->screen_x1 > WINDOW_WIDTH) 
    //     game->screen_x1 = WINDOW_WIDTH;
    tex_x = choose_texture(game, &tex,ray);
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