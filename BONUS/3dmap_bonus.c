/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3dmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:59:13 by aymisbah          #+#    #+#             */
/*   Updated: 2025/10/19 13:39:35 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	coor_calculation(t_texture *tex, float height_w)
{
	tex->top = (int)(WINDOW_HEIGHT / 2 - height_w / 2);
	tex->down = (int)(WINDOW_HEIGHT / 2 + height_w / 2);
	if (tex->top < 0)
		tex->top = 0;
	if (tex->down > WINDOW_HEIGHT)
		tex->down = WINDOW_HEIGHT;
	tex->tex_step = (float)tex->height / height_w;
	tex->tex_pos = (tex->top - WINDOW_HEIGHT / 2 + height_w / 2)
		* tex->tex_step;
}

void	draw(t_game *game, t_texture *tex, float tex_x, float height_w)
{
	int	i;
	int	j;
	int	tex_y;
	int	color;

	coor_calculation(tex, height_w);
	i = game->s_col;
	while (i < game->e_col)
	{
		j = tex->top;
		while (j < tex->down)
		{
			tex_y = (int)tex->tex_pos;
			if (tex_y < 0)
				tex_y = 0;
			color = get_tex_color(tex, (int)(tex_x), tex_y);
			put_pixel(game, i, j, color);
			tex->tex_pos += tex->tex_step;
			j++;
		}
		i++;
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
	if (ray->side == 'w' || ray->side == 'e')
		*tex_x = fmodf(ray->y, game->t_size) / game->t_size * (*tex)->width;
	else
		*tex_x = fmodf(ray->x, game->t_size) / game->t_size * (*tex)->width;
}

void	render_map(t_game *game, float height_w, int i)
{
	t_ray		*ray;
	t_texture	*tex;
	float		tex_x;

	ray = &game->rays[i];
	game->s_col = (i * WINDOW_WIDTH) / NUM_RAYS;
	game->e_col = ((i + 1) * WINDOW_WIDTH) / NUM_RAYS;
	choose_texture(game, ray, &tex, &tex_x);
	draw(game, tex, tex_x, height_w);
}

void	c_f_colors(t_game *game)
{
	int	c_color;
	int	f_color;
	int	x;
	int	y;

	c_color = rgb_to_int(game->info.cceiling[0], game->info.cceiling[1],
			game->info.cceiling[2]);
	f_color = rgb_to_int(game->info.cfloor[0], game->info.cfloor[1],
			game->info.cfloor[2]);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGHT)
		{
			if (y < WINDOW_HEIGHT / 2)
				put_pixel(game, x, y, c_color);
			else
				put_pixel(game, x, y, f_color);
			y++;
		}
		x++;
	}
}
