/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymisbah <aymisbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:50:06 by aymisbah          #+#    #+#             */
/*   Updated: 2025/10/27 12:54:20 by aymisbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <limits.h>

# define PI 3.14159265358979323846

# define TWO_PI 6.28318530

# define TILE_SIZE 32

# define ROWS 20
# define COLMS 20

# define WINDOW_WIDTH 1240
# define WINDOW_HEIGHT 1240

# define KEY_W 'w'
# define KEY_S 's'
# define KEY_A 'a'
# define KEY_D 'd'
# define KEY_E 'e'
# define KEY_SPACE ' '
# define ON_MOUSEMOVE 6

# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define WHITE 0xFFFFFF
# define YELLOW 0xFFFF00
# define BLACK 0x000000
# define RED 0xFF0000
# define BLUE 0x0000FF

# define NUM_RAYS 1240

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_info
{
	char		**map;
	int			fd;
	int			height;
	char		*north;
	char		*east;
	char		*west;
	char		*south;
	char		*door;
	char		*anim[4];
	int			n_cfloor;
	int			n_cceiling;
	int			cfloor[3];
	int			cceiling[3];
	char		direc;
}				t_info;

typedef struct s_sprite
{
	int			sprite_height;
	int			sprite_width;
	float		scale;
	int			start_x;
	int			start_y;
	int			screen_x;
	int			screen_y;
	int			color;
	int			tex_x;
	int			tex_y;
}				t_sprite;

typedef struct s_rect
{
	int			x;
	int			y;
	float		height;
	float		width;
	int			color;
}				t_rect;

typedef struct s_player
{
	float		x;
	float		y;
	float		width;
	float		height;
	int			trn_dr;
	int			ud_dr;
	float		rotat_ang;
	float		speed_w;
	float		ad_dr;
	float		speed_t;
}				t_player;

typedef struct s_ray
{
	float		x;
	float		y;
	float		angle;
	float		dx;
	float		dy;
	float		distance;
	float		inc_x;
	float		inc_y;
	char		side;
	int			door;
}				t_ray;

typedef struct s_texture
{
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bpp;
	int			line_len;
	int			endian;
	int			top;
	int			down;
	float		tex_pos;
	float		tex_step;
}				t_texture;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bpp;
	int			line_len;
	int			endian;
	int			m_ht;
	int			m_wd;
	int			t_size;
	int			anim_val;
	int			i_x;
	int			i_y;
	int			angle_x;
	int			angle_y;
	float		pd_x;
	float		pd_y;
	float		cd_x;
	float		cd_y;
	int			e_col;
	int			s_col;
	float		fov;
	t_player	player;
	t_info		info;
	t_ray		rays[NUM_RAYS];
	int			last_x;
	t_texture	textures[9];
}				t_game;

void			initialize(t_game *game);
void			wall_free(t_game *game);
char			*get_next_line(int fd);
int				parsing(char *filename, t_info *info);
int				valid_filename(char *str);
char			*extract_line(char *line);
char			*ft_strjoin(char *s1, char *s2);
int				ft_strlen(char *s);
char			*trim_to_next_line(char *line);
char			*ft_strdup(char *s);
void			ft_strcopy(char *dst, char *src);
void			free_str(char **str);
int				ft_strncmp(char *s1, char *s2, int n);
char			**ft_split(char const *s, char c);
void			ft_free(char **tab);
int				ft_atoi(char *str);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
void			*ft_memset(void *b, int c, size_t len);
void			ft_clean(t_info *info);
void			parse_color(char *str, t_info *info);
int				is_color(char *str);
int				is_map(char *str);
int				check_map(t_info *info, int height);
int				count_direction(char **str, char *dirc);
void			parse_map(char *str, t_info *info);
int				is_texter(char *str);
void			parse_texter(char *str, t_info *info);
void			error_handler(char *str, t_info *info);
int				check_space(char **info, char dirc);
void			change_space(char **map);
void			map_2d(t_game *game);
void			put_pixel(t_game *game, int x, int y, int color);
void			render_rays(t_game *game);
void			map_3d(t_game *game);
int				get_tex_color(t_texture *tex, int x, int y);
int				rgb_to_int(int r, int g, int b);
void			animation(t_game *game);
int				mouse_hook(int x, int y, t_game *game);
int				handle_input(int key, t_game *game);
int				release_input(int key, t_game *game);
void			update_player(t_game *game);
void			init_textures(t_game *game);
void			assign_path(t_game *game, char *path[9]);
void			render_ray(t_game *game, float curr_a, int i);
void			render_map(t_game *game, float height_w, int i);
void			c_f_colors(t_game *game);
void			open_door(t_game *game);
void			free_txt(t_info *info);
void			close_pr(t_game *game);
void			show_user_info(void);
#endif
