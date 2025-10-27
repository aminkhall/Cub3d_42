/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymisbah <aymisbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:49:58 by aymisbah          #+#    #+#             */
/*   Updated: 2025/10/27 12:55:28 by aymisbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	map_3d(t_game *game)
{
	int		i;
	float	proj_dst;
	float	dst;
	float	height_w;

	c_f_colors(game);
	proj_dst = (WINDOW_WIDTH / 2) / tan(game->fov / 2);
	i = -1;
	while (++i < NUM_RAYS)
	{
		dst = game->rays[i].distance;
		height_w = (game->t_size / dst) * proj_dst;
		render_map(game, height_w, i);
	}
}

void	render_rays(t_game *game)
{
	float	first_a;
	float	step;
	float	curr_a;
	int		i;

	first_a = game->player.rotat_ang - (game->fov / 2);
	step = game->fov / (NUM_RAYS);
	i = -1;
	while (++i < NUM_RAYS)
	{
		curr_a = first_a + i * step;
		render_ray(game, curr_a, i);
	}
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
	update_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	mlx_destroy_image(game->mlx, game->img);
	game->img = NULL;
	return (0);
}

int	quit(t_game *game)
{
	ft_clean(&game->info);
	free_txt(&game->info);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(0);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (ac != 2)
		return (1);
	if (!valid_filename(av[1]))
		return (1);
	if (!parsing(av[1], &game.info))
		return (ft_clean(&game.info), 1);
	show_user_info();
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub");
	initialize(&game);
	mlx_hook(game.win, ON_MOUSEMOVE, 1L << 6, mouse_hook, &game);
	mlx_hook(game.win, 2, 1L << 0, handle_input, &game);
	mlx_hook(game.win, 3, 1L << 1, release_input, &game);
	mlx_hook(game.win, 17, 0, quit, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
