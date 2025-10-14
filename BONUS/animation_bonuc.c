/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonuc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:21:43 by mkhallou          #+#    #+#             */
/*   Updated: 2025/10/10 16:32:20 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	draw_sprite_centered(t_game *game, t_texture *tex)
{
	int		sprite_height;
	int		sprite_width;
	float	scale;
	int		start_x;
	int		start_y;
	int		screen_x;
	int		screen_y;
	int		color;
	int		tex_x;
	int		tex_y;

	scale = (WINDOW_HEIGHT / 2.5f) / tex->height;
	sprite_height = (int)(tex->height * scale);
	sprite_width = (int)(tex->width * scale);
	start_x = (WINDOW_WIDTH / 2) - (sprite_width / 2);
	start_y = WINDOW_HEIGHT - sprite_height;
	for (int x = 0; x < sprite_width; x++)
	{
		screen_x = start_x + x;
		if (screen_x < 0 || screen_x >= WINDOW_WIDTH)
			continue ;
		for (int y = 0; y < sprite_height; y++)
		{
			screen_y = start_y + y;
			if (screen_y < 0 || screen_y >= WINDOW_HEIGHT)
				continue ;
			tex_x = (int)((x / (float)sprite_width) * tex->width);
			tex_y = (int)((y / (float)sprite_height) * tex->height);
			color = get_tex_color(tex, tex_x, tex_y);
			if ((color & 0x00FFFFFF) != 0)
				put_pixel(game, screen_x, screen_y, color);
		}
	}
}
void	animation(t_game *game)
{
	t_texture *tex;
	int i;

	if (!game->anim_val)
	{
		tex = &game->textures[5];
		draw_sprite_centered(game, tex);
	}
	else
	{
		i = 6;
		while (i < 9)
		{
			tex = &game->textures[i];
			draw_sprite_centered(game, tex);
			++i;
		}
	}
}
