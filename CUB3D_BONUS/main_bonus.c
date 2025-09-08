/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:49:58 by aymisbah          #+#    #+#             */
/*   Updated: 2025/09/08 14:14:42 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"


void put_pixel(t_game *game, int x, int y, int color)
{
    if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
        return;
    char *dst = game->addr + (y * game->line_len + x * (game->bpp / 8));
    *(unsigned int *)dst = color;
}

int rgb_to_int(int r, int g, int b)
{
    return ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff);
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
    if (mapX < 0 || mapX >= game->map_width || mapY < 0 || mapY >= game->map_height)
        return 1;
    char c = game->info.map[mapY][mapX];
    return (c != '0' && c != 'O');
}
int is_do(float x, float y, t_game *game)
{
    float padding = 0.1f; // in pixels or fraction of tile
    int mapX = (int)((x + padding) / game->tile_size);
    int mapY = (int)((y + padding) / game->tile_size);
    if (mapX < 0 || mapX >= game->map_width || mapY < 0 || mapY >= game->map_height)
        return 0;
    char c = game->info.map[mapY][mapX];
    return (c == 'D' || c == 'O');
}

void open_door(t_game *game)
{
    t_player *p = &game->player;

    // Look 1/2 tile forward
    float checkX = p->x + cos(p->rotationAngle) * (game->tile_size);
    float checkY = p->y + sin(p->rotationAngle) * (game->tile_size);

    int mapX = (int)(checkX / game->tile_size);
    int mapY = (int)(checkY / game->tile_size);

    if (mapX < 0 || mapX >= game->map_width ||
        mapY < 0 || mapY >= game->map_height)
        return;
    if (game->info.map[mapY][mapX] == 'D')
        game->info.map[mapY][mapX] = 'O';
    else if (game->info.map[mapY][mapX] == 'O')
        game->info.map[mapY][mapX] = 'D';
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
    if (!is_wall(newX, game->player.y, game))
        p->x = newX;
    if (!is_wall(game->player.x, newY, game))
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
    else if (key == KEY_SPACE)
        open_door(game);
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

int mouse_hook(int x, int y, t_game *game)
{
    static int last_x = -1;
    int dx;

    if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
        return (1);
    if (last_x == -1)
    {
        last_x = x;
        return (0);
    }

    dx = x - last_x;
    
    if (dx < 0)
        game->player.turnDirection = -1;  // turn left
    else if (dx > 0)
        game->player.turnDirection = 1;   // turn right
    else
        game->player.turnDirection = 0;   // no turn

    last_x = x;
    return (0);
}

void render_ray(t_game *game, float ray_angle, int id)
{
    t_ray *ray = &game->rays[id];
    ray->x = game->player.x;
    ray->y = game->player.y;

    ray_angle = fmod(ray_angle, TWO_PI);
    if (ray_angle < 0) 
        ray_angle += TWO_PI;
        
    float step_size = 0.2f;

    while (1)
    {
        float distX = cos(ray_angle) * step_size;
        float distY = sin(ray_angle) * step_size;
        float newX = ray->x + distX;
        float newY = ray->y + distY;
        if (is_wall(newX, ray->y, game))
        {
            ray->x = newX;
            if (is_do(newX, ray->y, game))
                ray->side = 'd';
            else if (cos(ray_angle) > 0)
                ray->side = 'e';
            else
                ray->side = 'w';
            break ;
        }
        if (is_wall(ray->x, newY, game))
        {
            ray->y = newY;
            if (is_do(ray->x, newY, game))
                ray->side = 'd';
            else if (sin(ray_angle) > 0)
                ray->side = 's';
            else
                ray->side = 'n';   
            break ;
        }
        ray->x = newX;
        ray->y = newY;
    }
    ray->dx = ray->x - game->player.x;
    ray->dy = ray->y - game->player.y;
    // fisheye correction
    float relative_angle = game->player.rotationAngle - ray_angle; 
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
    {
        tex = &game->textures[0];
        tex_x = fmodf(ray->x, game->tile_size) / game->tile_size * tex->width;
    } 
    else if (ray->side == 's') 
    {
        tex = &game->textures[1];
        tex_x = fmodf(ray->x, game->tile_size) / game->tile_size * tex->width;
    } 
    else if (ray->side == 'e') 
    {
        tex = &game->textures[2];
        tex_x = fmodf(ray->y, game->tile_size) / game->tile_size * tex->width;
    } 
    else if (ray->side == 'w')
    {
        tex = &game->textures[3]; 
        tex_x = fmodf(ray->y, game->tile_size) / game->tile_size * tex->width;
    }
    else
    {
        tex = &game->textures[4]; 
        tex_x = fmodf(ray->y, game->tile_size) / game->tile_size * tex->width;
    }
    if (tex_x < 0) 
        tex_x += tex->width;
    int x = screen_x0;
    
    while (x < screen_x1) 
    {
        int y = top;
        while (y < bottom) 
        {
            float t = (float)(y - top) / (float)(bottom - top);
            int tex_y = (int)(t * tex->height);
            if (tex_y < 0) 
                tex_y = 0;
            if (tex_y >= tex->height) 
                tex_y = tex->height - 1;
            int color = get_tex_color(tex, (int)tex_x, tex_y);
            put_pixel(game, x, y, color);
            y++;
        }
        x++;
    }
}



void map_3d(t_game *game)
{
    int ceil_color;
    int floor_color;
    int x;
    int i;
    int y;
    float proj_dist;

    ceil_color = rgb_to_int(game->info.cceiling[0], game->info.cceiling[1], game->info.cceiling[2]);
    floor_color = rgb_to_int(game->info.cfloor[0],   game->info.cfloor[1],   game->info.cfloor[2]);
    x = 0;
    while (x < WINDOW_WIDTH) 
    {
        y = 0;
        while (y < WINDOW_HEIGHT) 
        {
            put_pixel(game, x, y, (y < WINDOW_HEIGHT / 2) ? ceil_color : floor_color);
            y++;
        }
        x++;
    }
    proj_dist = (WINDOW_WIDTH / 2.0f) / tanf(FOV_ANGLE / 2.0f);
    i = 0;
    while (i < NUM_RAYS) 
    {
        float dist = game->rays[i].distance;
        if (dist < 0.0001f) 
            dist = 0.0001f;
        float wall_height = (game->tile_size / dist) * proj_dist;
        if (wall_height < 1.0f) 
            wall_height = 1.0f;
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
    map_2d(game);
    // render_minimap(game);
    update_player(game);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    mlx_destroy_image(game->mlx, game->img);
    return 0;
}

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

void init_textures(t_game *game)
{
    char *path[5] ;
    int i = 0;
    
    path[0] = game->info.north; 
    path[1] = game->info.south; 
    path[2] = game->info.east; 
    path[3] = game->info.west;
    path[4] = game->info.door;
    while (i < 5)
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


void initialize(t_game *game)
{
    game->tile_size = TILE_SIZE;
    game->player.walkSpeed = 5;
    game->player.turnSpeed = 0.03f;
    
    map_dimensions(game);
    init_textures(game); 
    player_pos(game);
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
    mlx_hook(game.win, ON_MOUSEMOVE, 1L<<6, mouse_hook, &game);
    mlx_loop_hook(game.mlx, game_loop, &game);
    mlx_loop(game.mlx);
    return 0;
}