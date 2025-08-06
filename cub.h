#ifndef CUB_H
#define CUB_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
# include <fcntl.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
char	*extract_line(char *line);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*trim_to_next_line(char *line);
char	*ft_strdup(char *s);
void	ft_strcopy(char *dst, char *src);
void	free_str(char **str);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
void	ft_free(char **tab);
int     ft_atoi(const char *str);


typedef struct s_info
{
    char **map;
    char *north;
    char *east;
    char *west;
    char *south;
    int **cfloor;
    int **cceiling;
} t_info;


#endif