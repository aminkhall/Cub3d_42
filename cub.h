#ifndef CUB_H
#define CUB_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*extract_line(char *line);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*trim_to_next_line(char *line);
char	*ft_strdup(char *s);
void	ft_strcopy(char *dst, char *src);
void	free_str(char **str);
int	    ft_strncmp(char *s1, char *s2, int n);
char	**ft_split(char const *s, char c);
void	ft_free(char **tab);
int     ft_atoi(char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	*ft_memset(void *b, int c, size_t len);


typedef struct s_info
{
    char **map;
    int  height;
    char *north;
    char *east;
    char *west;
    char *south;
    int cfloor[3];
    int cceiling[3];
} t_info;


#endif