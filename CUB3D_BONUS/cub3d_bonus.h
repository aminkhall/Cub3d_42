/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:50:06 by aymisbah          #+#    #+#             */
/*   Updated: 2025/09/11 20:12:33 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <unistd.h>
// # include <mlx.h>
#include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <limits.h>


// #define PI 3.14159265
#define PI 3.14159265358979323846

#define TWO_PI 6.28318530

#define TILE_SIZE 32
#define MINIMAP_SCALE 0.12f

#define MINIMAP_WIDTH 200
#define MINIMAP_HEIGHT 200

#define ROWS 20
#define COLMS 20

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 1024

#define FOV_ANGLE (60 * (PI / 180))


// #define KEY_ESC    53
#define KEY_W      'w'
#define KEY_S      's'
#define KEY_A      'a'
#define KEY_D      'd'
#define KEY_E      'e'
#define KEY_SPACE ' '
#define ON_MOUSEMOVE   6
// #define KEY_W   13
// #define KEY_A   0
// #define KEY_S   1
// #define KEY_D   2
// #define KEY_SPACE 49

// #define KEY_LEFT   123
/// mac 
// #define KEY_ESC    53
// #define KEY_LEFT   123
// #define KEY_RIGHT  124

//////// linux
#define KEY_ESC     65307
#define KEY_LEFT    65361
#define KEY_RIGHT   65363

#define WHITE 0xFFFFFF
#define YELLOW 0xFFFF00 
#define BLACK 0x000000
#define RED 0xFF0000
#define BLUE 0x0000FF


#define NUM_RAYS 1024
#define FOV (60 * (PI / 180)) 
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif


// Parsing Struct
typedef struct s_info
{
	char	**map;
	int		fd;
	int		height;
	char	*north;
	char	*east;
	char	*west;
	char	*south;
    char    *door;
    char    *anim[2];
	int		n_cfloor;
	int		n_cceiling;
	int		cfloor[3];
	int		cceiling[3];
    char    direc;
}			t_info;

typedef struct s_player {
    float x;
    float y;
    float width;
    float height;
    int turnDirection;
    int walkDirection;
    float rotationAngle;
    float walkSpeed;
    float strafeDirection;
    float turnSpeed;
}   t_player;

typedef struct s_ray {
    float x;
    float y;
    float angle;
    float dx;
    float dy;
    float distance;
    float inc_x;
    float inc_y;
    char side;
} t_ray;

typedef struct s_texture {
    void    *img;
    char    *addr;
    int     width;
    int     height;
    int     bpp;
    int     line_len;
    int     endian;
}   t_texture;

typedef struct s_game {
    void        *mlx;
    void        *win;
    void        *img;
    char        *addr;
    int         width;
    int         height;
    int         bpp;
    int         line_len;
    int         endian;
    int         map_height;
    int         map_width; 
    int         tile_size;
    int         anim_val;
    t_player    player;
    t_info      info;
    t_ray       rays[NUM_RAYS];

    t_texture   textures[7]; // 0=NORTH, 1=SOUTH, 2=EAST, 3=WEST, 4=DOOR, 5=ANIM1, 6=ANIM2
}   t_game;

void	initialize(t_game *game);
void	wall_free(t_game *game);

// >>>>>>>>>>>>>>>>>>>>>>>>>> Parsing <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
char		*get_next_line(int fd);
int	parsing(char *filename, t_info *info);
int	valid_filename(char *str);
char		*extract_line(char *line);
char		*ft_strjoin(char *s1, char *s2);
int		    ft_strlen(char *s);
char		*trim_to_next_line(char *line);
char		*ft_strdup(char *s);
void		ft_strcopy(char *dst, char *src);
void		free_str(char **str);
int			ft_strncmp(char *s1, char *s2, int n);
char		**ft_split(char const *s, char c);
void		ft_free(char **tab);
int			ft_atoi(char *str);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
void		*ft_memset(void *b, int c, size_t len);
void		ft_clean(t_info *info);
void		parse_color(char *str, t_info *info);
int			is_color(char *str);
int			is_map(char *str);
int			check_map(t_info *info, int height);
int			count_direction(char **str, char *dirc);
void		parse_map(char *str, t_info *info);
int			is_texter(char *str);
int			check_texter(t_info *info);
void		parse_texter(char *str, t_info *info);
void		error_handler(char *str, t_info *info);
int			check_space(char **info, char dirc);
void		change_space(char **map);
void        map_2d(t_game *game);
void        put_pixel(t_game *game, int x, int y, int color);
int         is_door(char *str);
void        parse_door(char *str, t_info *info);

#endif
