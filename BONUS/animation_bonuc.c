/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonuc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:21:43 by mkhallou          #+#    #+#             */
/*   Updated: 2025/10/14 15:35:36 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	draw_sprite_centered(t_game *game, t_texture *tex)
{
	t_sprite	sprit;
	int			x;
	int			y;

	sprit.scale = (WINDOW_HEIGHT / 2.5f) / tex->height;
	sprit.sprite_height = (int)(tex->height * sprit.scale);
	sprit.sprite_width = (int)(tex->width * sprit.scale);
	sprit.start_x = (WINDOW_WIDTH / 2) - (sprit.sprite_width / 2);
	sprit.start_y = WINDOW_HEIGHT - sprit.sprite_height;
	x = -1;
	while (++x < sprit.sprite_width)
	{
		y = -1;
		sprit.screen_x = sprit.start_x + x;
		while (++y < sprit.sprite_height)
		{
			sprit.screen_y = sprit.start_y + y;
			sprit.tex_x = (int)((x / (float)sprit.sprite_width) * tex->width);
			sprit.tex_y = (int)((y / (float)sprit.sprite_height) * tex->height);
			sprit.color = get_tex_color(tex, sprit.tex_x, sprit.tex_y);
			if ((sprit.color & 0x00FFFFFF) != 0)
				put_pixel(game, sprit.screen_x, sprit.screen_y, sprit.color);
		}
	}
}

void	animation(t_game *game)
{
	t_texture	*tex;
	int			i;

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
