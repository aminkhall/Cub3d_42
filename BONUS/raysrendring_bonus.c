/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raysrendring.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymisbah <aymisbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:58:47 by aymisbah          #+#    #+#             */
/*   Updated: 2025/10/18 17:44:26 by aymisbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	check_wall(t_game *game, int i_x, int i_y)
{
	char	grid;

	grid = game->info.map[i_y][i_x];
	if (grid != '0' && grid != 'O')
		return (1);
	return (0);
}

void	check_sides(t_game *game, t_ray *ray)
{
	char	index;

	while (!check_wall(game, game->i_x, game->i_y))
	{
		if (game->pd_x < game->pd_y)
		{
			game->pd_x += game->cd_x;
			game->i_x += game->angle_x;
			if ((game->angle_x > 0))
				ray->side = 'e';
			else
				ray->side = 'w';
		}
		else
		{
			game->pd_y += game->cd_y;
			game->i_y += game->angle_y;
			if ((game->angle_y > 0))
				ray->side = 's';
			else
				ray->side = 'n';
		}
	}
	index = game->info.map[game->i_y][game->i_x];
	ray->door = (index == 'D' || index == 'O');
}

void	grid_distance(t_game *game, t_ray *ray, float curr_a)
{
	if (cos(curr_a) < 0)
		game->angle_x = -1;
	else
		game->angle_x = 1;
	if (sin(curr_a) < 0)
		game->angle_y = -1;
	else
		game->angle_y = 1;
	if (game->angle_x > 0)
		game->pd_x = (((game->i_x + 1) * game->t_size) - game->player.x)
			* game->cd_x / game->t_size;
	else
		game->pd_x = (game->player.x - (game->i_x * game->t_size))
			* game->cd_x / game->t_size;
	if (game->angle_y > 0)
		game->pd_y = (((game->i_y + 1) * game->t_size) - game->player.y)
			* game->cd_y / game->t_size;
	else
		game->pd_y = (game->player.y - (game->i_y * game->t_size))
			* game->cd_y / game->t_size;
	check_sides(game, ray);
}

void	hit_point(t_game *game, t_ray *ray, float curr_a)
{
	float	ray_ang;

	if (ray->side == 'e' || ray->side == 'w')
	{
		ray->x = game->player.x + cos(curr_a) * (game->pd_x - game->cd_x);
		ray->y = game->player.y + sin(curr_a) * (game->pd_x - game->cd_x);
	}
	else
	{
		ray->x = game->player.x + cos(curr_a) * (game->pd_y - game->cd_y);
		ray->y = game->player.y + sin(curr_a) * (game->pd_y - game->cd_y);
	}
	ray_ang = curr_a - game->player.rotat_ang;
	ray->distance = sqrt((ray->x - game->player.x) * (ray->x - game->player.x)
			+ (ray->y - game->player.y) * (ray->y - game->player.y));
	ray->distance *= cos(ray_ang);
}

void	render_ray(t_game *game, float curr_a, int i)
{
	t_ray	*ray;

	ray = &game->rays[i];
	game->i_x = (int)(game->player.x / game->t_size);
	game->i_y = (int)(game->player.y / game->t_size);
	game->cd_x = game->t_size / fabs(cos(curr_a));
	game->cd_y = game->t_size / fabs(sin(curr_a));
	grid_distance(game, ray, curr_a);
	hit_point(game, ray, curr_a);
}
