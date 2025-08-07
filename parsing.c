#include "cub.h"

int is_texter(char *str)
{
    char **line = ft_split(str, ' ');
    if (!ft_strncmp(line[0], "NO", 3))
        return (1);
    else if (!ft_strncmp(line[0], "SO", 3))
        return (1);
    else if (!ft_strncmp(line[0], "WE", 3))
        return (1);
    else if (!ft_strncmp(line[0], "EA", 3))
        return (1);
    return (0);
}

int is_color(char *str)
{
    char **line = ft_split(str, ' ');
    if (!ft_strncmp(line[0], "F", 2))
        return (1);
    else if (!ft_strncmp(line[0], "C", 2))
        return (1);
    return (0);
}

int is_map(char *str)
{
    if (*str == '1')
        return (1);
    return (0);
}

int count_direction(char *str)
{
    int count;

    count = 0;
    while (*str)
    {
        if (*str == 'N' || *str == 'E' || *str == 'S' || *str == 'W')
            ++count;
        ++str;
    }
    return (count);
}

int valid_map(char *str)
{
    printf("%s\n", str);
    int len = ft_strlen(str);
    if (str[0] != '1' && str[len] != '1')
        return (0);
    while (*str)
    {
        if (*str != '1' && *str != '0' && *str != 'N' && *str != 'E' && *str != 'S' && *str != 'W' && *str != ' ')
            return (0);
        ++str;
    }
    return (1);
}

void    parse_map(char *str, t_info *info)
{
    if (!valid_map(str))
        return ;
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

int get_color(char *str, int rgb[3])
{
    char **color;

    if (!str)
        return (-1);
    color = ft_split(str, ',');
    if (!color || !color[0] || !color[1] || !color[2])
        return (-1);
    rgb[0] = ft_atoi(color[0]);
    rgb[1] = ft_atoi(color[1]);
    rgb[2] = ft_atoi(color[2]);
    ft_free(color);
    return (0);
}

void    parse_color(char *str, t_info *info)
{
    char **line;

    line = ft_split(str, ' ');
    if (!line || !line[0] || !line[1])
        return ;
    if (!ft_strncmp(line[0], "F", 2))
        get_color(line[1], info->cfloor);
    else if (!ft_strncmp(line[0], "C", 2))
        get_color(line[1], info->cceiling);
    ft_free(line);
}

int parsing(char *filename, t_info *info)
{
    char *line;
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (0);
    while ((line = get_next_line(fd)))
    {
        if (is_texter(line))
            parse_texter(line, info);
        else if (is_color(line))
            parse_color(line, info);
        else if (is_map(line))
            parse_map(line, info);
        else
            return (0);
        free(line);
    }
    close(fd);
    return (1);
}

int main(int ac, char **av)
{
    t_info info;
    ft_memset(&info, 0, sizeof(t_info));
    if (!parsing("text.cub", &info))
        return (1);
    printf("%d\n%d\n%d\n", info.cfloor[0], info.cfloor[1], info.cfloor[2]);
    printf("%d\n%d\n%d\n", info.cceiling[0], info.cceiling[1], info.cceiling[2]);
    printf("%s\n%s\n%s\n%s\n", info.east, info.north, info.south, info.west);
    return (0);
}