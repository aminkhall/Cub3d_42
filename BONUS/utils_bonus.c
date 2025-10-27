/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:59:16 by aymisbah          #+#    #+#             */
/*   Updated: 2025/10/19 16:14:26 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_textures(t_game *game)
{
	char	*path[9];
	int		i;

	i = 0;
	assign_path(game, path);
	while (i < 9)
	{
		game->textures[i].img = mlx_xpm_file_to_image(game->mlx, path[i],
				&game->textures[i].width, &game->textures[i].height);
		if (!game->textures[i].img)
		{
			close_pr(game);
			printf("Error: Failed to load texture %s\n", path[i]);
			exit(1);
		}
		game->textures[i].addr = mlx_get_data_addr(game->textures[i].img,
				&game->textures[i].bpp, &game->textures[i].line_len,
				&game->textures[i].endian);
		i++;
	}
}

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = game->addr + (y * game->line_len + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}

int	rgb_to_int(int r, int g, int b)
{
	return (((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff));
}

int	get_tex_color(t_texture *tex, int x, int y)
{
	char	*dst;

	dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

void	show_user_info(void)
{
	printf("=== Controls Info ===\n");
	printf("%-20s : %s\n", "Move Forward", "'W'");
	printf("%-20s : %s\n", "Move Backward", "'S'");
	printf("%-20s : %s\n", "Move Left", "'A'");
	printf("%-20s : %s\n", "Move Right", "'D'");
	printf("%-20s : %s\n", "Animation", "'E'");
	printf("%-20s : %s\n", "Open/Close Door", "'SPACE'");
	printf("%-20s : %s\n", "Turn Left", "'Left Arrow'");
	printf("%-20s : %s\n", "Turn Right", "'Right Arrow'");
	printf("%-20s : %s\n", "Exit/Quit", "'ESC'");
	printf("%-20s : %s\n", "Change direction", "'MOUSEMOVE'");
}
