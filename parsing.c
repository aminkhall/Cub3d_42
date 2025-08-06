#include "cub.h"

int is_texter(char *str)
{
    if (!ft_strncmp(str, "NO", 3))
        return (1);
    else if (!ft_strncmp(str, "SO", 3))
        return (1);
    else if (!ft_strncmp(str, "WE", 3))
        return (1);
    else if (!ft_strncmp(str, "EA", 3))
        return (1);
    return (0);
}

int is_color(char *str)
{
    if (!ft_strncmp(str, "F", 2))
        return (1);
    else if (!ft_strncmp(str, "C", 2))
        return (1);
    return (0);
}


void    parse_texter(char *str, t_info *info)
{
    char **line;

    line = ft_split(str, ' ');
    if (!line || !line[0] || !line[1])
        return ;
    if (!ft_strncmp(line[0], "NO", 3))
        info->north = ft_strdup(line[1]);
    else if (!ft_strncmp(line[0], "SO", 3))
        info->south = ft_strdup(line[1]);
    else if (!ft_strncmp(line[0], "WE", 3))
        info->west = ft_strdup(line[1]);
    else if (!ft_strncmp(line[0], "EA", 3))
        info->east = ft_strdup(line[1]);
    ft_free(line);
    return ;
}

int **get_color(char *str)
{
    char **color;

    if (!str)
        return (NULL);
    color = ft_split(str, ',');
    if (!color || !color[0] || !color[1] || !color[2])
        return (-1);
    int r = ft_atoi(color[0]);
    int g = ft_atoi(color[1]);
    int b = ft_atoi(color[2]);
}

void    parse_color(char *str, t_info *info)
{
    char **line;
    char **color;

    line = ft_split(str, ' ');
    if (!line || !line[0] || !line[1])
        return ;
    if (!ft_strncmp(line[0], "F", 2))
        info->cfloor = get_color(line[1]);
    else if (!ft_strncmp(line[0], "C", 2))
        info->cceiling = get_color(line[1]);
    ft_free(line);
}

int parsing(char *filename, t_info *info)
{
    char *line;
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (0);
    while (line = get_next_line(1))
    {
        if (is_texter(line))
            parse_texter(line, info);
        else if (is_color(line))
            parse_color(line, info);
        free(line);
    }
    
}

// int main(int ac, char **av)
// {
//     if (parsing(av))
//         return (1);
//     return (0);
// }