/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:49:58 by aymisbah          #+#    #+#             */
/*   Updated: 2025/10/09 15:44:04 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	return ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff);
}

int	get_tex_color(t_texture *tex, int x, int y)
{
	char	*dst;

	dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

int	is_wall(float x, float y, t_game *game)
{
	int		mapX;
	int		mapY;
	char	c;

	mapX = (int)(x / game->tile_size);
	mapY = (int)(y / game->tile_size);
	if (mapX < 0 || mapX >= game->map_width || mapY < 0
		|| mapY >= game->map_height)
		return (1);
	c = game->info.map[mapY][mapX];
	return (c != '0' && c != 'O'); // wall or closed door
}

void	update_player(t_game *game)
{
	t_player	*p;
	float		moveStep;
	float		strafeStep;
	float		newX;
	float		newY;

	p = &game->player;
	p->rotationAngle += p->turnDirection * p->turnSpeed;
	moveStep = p->walkDirection * p->walkSpeed;
	strafeStep = p->strafeDirection * p->walkSpeed;
	newX = p->x + cos(p->rotationAngle) * moveStep + cos(p->rotationAngle + PI
			/ 2) * strafeStep;
	newY = p->y + sin(p->rotationAngle) * moveStep + sin(p->rotationAngle + PI
			/ 2) * strafeStep;
	float margin = 5; // pixels, like player "radius"
	if (!is_wall(newX + margin, game->player.y, game) && !is_wall(newX - margin,
			game->player.y, game))
		p->x = newX;
	if (!is_wall(game->player.x, newY + margin, game)
		&& !is_wall(game->player.x, newY - margin, game))
		p->y = newY;
	game->player.turnDirection = 0;
}

int	handle_input(int key, t_game *game)
{
	if (key == KEY_ESC)
	{
		ft_clean(&game->info);
		free_txt(&game->info);
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
	else if (key == KEY_SPACE)
		open_door(game);
	else if (key == KEY_E)
		game->anim_val = 1;
	return (0);
}

int	release_input(int key, t_game *game)
{
	if (key == KEY_W || key == KEY_S)
		game->player.walkDirection = 0;
	else if (key == KEY_D || key == KEY_A)
		game->player.strafeDirection = 0;
	else if (key == KEY_LEFT || key == KEY_RIGHT)
		game->player.turnDirection = 0;
	else if (key == KEY_E)
		game->anim_val = 0;
	return (0);
}



int	game_loop(t_game *game)
{
	game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game->addr = mlx_get_data_addr(game->img, &game->bpp, &game->line_len,
			&game->endian);
	render_rays(game);
	map_3d(game);
	map_2d(game);
	animation(game);
	// render_minimap(game);
	update_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	mlx_destroy_image(game->mlx, game->img);
	return (0);
}

int	main(int ac, char **av)
{
	t_game game;

	ft_memset(&game, 0, sizeof(t_game));
	if (ac != 2)
		return (1);
	if (!valid_filename(av[1]))
		return (1);
	if (!parsing(av[1], &game.info))
		return (ft_clean(&game.info), 1);
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub");
	initialize(&game);
	mlx_hook(game.win, ON_MOUSEMOVE, 1L << 6, mouse_hook, &game);
	mlx_hook(game.win, 2, 1L << 0, handle_input, &game);
	mlx_hook(game.win, 3, 1L << 1, release_input, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	// ft_clean(&game.info);
	return (0);
}