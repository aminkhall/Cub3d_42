/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 18:10:03 by aymisbah          #+#    #+#             */
/*   Updated: 2025/10/19 16:12:12 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	printf("%-20s : %s\n", "Turn Left", "'Left Arrow'");
	printf("%-20s : %s\n", "Turn Right", "'Right Arrow'");
	printf("%-20s : %s\n", "Exit/Quit", "'ESC'");
}
