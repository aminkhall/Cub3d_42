
#include "cub3d_bonus.h"

int check_wall(t_game *game,int mapX,int mapY)
{
    char cell = game->info.map[mapY][mapX];
    if (cell != '0' && cell != 'O') 
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
    ray->door = (game->info.map[game->mapY][game->mapX] == 'D' || game->info.map[game->mapY][game->mapX] == 'O');
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