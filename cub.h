/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 20:14:00 by mkhallou          #+#    #+#             */
/*   Updated: 2025/08/10 16:03:07 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_info
{
	char	**map;
	int		fd;
	int		height;
	char	*north;
	char	*east;
	char	*west;
	char	*south;
	int		n_cfloor;
	int		n_cceiling;
	int		cfloor[3];
	int		cceiling[3];
}			t_info;

char		*get_next_line(int fd);
char		*extract_line(char *line);
char		*ft_strjoin(char *s1, char *s2);
size_t		ft_strlen(char *s);
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
int			count_direction(char **str);
void		parse_map(char *str, t_info *info);
int			is_texter(char *str);
int			check_texter(t_info *info);
void		parse_texter(char *str, t_info *info);
void		error_handler(char *str, t_info *info);
int			check_space(char **info);
void		change_space(char **map);

#endif