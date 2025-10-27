/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymisbah <aymisbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:44:11 by aymisbah          #+#    #+#             */
/*   Updated: 2025/10/18 18:02:41 by aymisbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	close_pr(t_game *game)
{
	ft_clean(&game->info);
	free_txt(&game->info);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}

int	is_wall(float x, float y, t_game *game)
{
	int		i_x;
	int		i_y;
	char	c;

	i_x = (int)(x / game->t_size);
	i_y = (int)(y / game->t_size);
	if (i_x < 0 || i_x >= game->m_wd || i_y < 0 || i_y >= game->m_ht)
		return (1);
	c = game->info.map[i_y][i_x];
	return (c != '0' && c != 'O');
}

void	update_player(t_game *game)
{
	t_player	*p;
	float		ud_step;
	float		ad_step;
	float		i_x;
	float		i_y;

	p = &game->player;
	p->rotat_ang += p->trn_dr * p->speed_t;
	ud_step = p->ud_dr * p->speed_w;
	ad_step = p->ad_dr * p->speed_w;
	i_x = p->x + cos(p->rotat_ang) * ud_step
		+ cos(p->rotat_ang + PI / 2) * ad_step;
	i_y = p->y + sin(p->rotat_ang) * ud_step
		+ sin(p->rotat_ang + PI / 2) * ad_step;
	if (!is_wall(i_x + 3, game->player.y, game)
		&& !is_wall(i_x - 3, game->player.y, game))
		p->x = i_x;
	if (!is_wall(game->player.x, i_y + 3, game)
		&& !is_wall(game->player.x, i_y - 3, game))
		p->y = i_y;
	game->player.trn_dr = 0;
}

int	handle_input(int key, t_game *game)
{
	if (key == KEY_ESC)
	{
		close_pr(game);
		exit(0);
	}
	if (key == KEY_W)
		game->player.ud_dr = +1;
	else if (key == KEY_S)
		game->player.ud_dr = -1;
	else if (key == KEY_A)
		game->player.ad_dr = -1;
	else if (key == KEY_D)
		game->player.ad_dr = +1;
	else if (key == KEY_LEFT)
		game->player.trn_dr = -1;
	else if (key == KEY_RIGHT)
		game->player.trn_dr = +1;
	else if (key == KEY_SPACE)
		open_door(game);
	else if (key == KEY_E)
		game->anim_val = 1;
	return (0);
}

int	release_input(int key, t_game *game)
{
	if (key == KEY_W || key == KEY_S)
		game->player.ud_dr = 0;
	else if (key == KEY_D || key == KEY_A)
		game->player.ad_dr = 0;
	else if (key == KEY_LEFT || key == KEY_RIGHT)
		game->player.trn_dr = 0;
	else if (key == KEY_E)
		game->anim_val = 0;
	return (0);
}
