#include "cub.h"

int is_texter(char *str)
{
    char **line = ft_split(str, ' ');
    if (!ft_strncmp(line[0], "NO", 3))
        return (ft_free(line), 1);
    else if (!ft_strncmp(line[0], "SO", 3))
        return (ft_free(line), 1);
    else if (!ft_strncmp(line[0], "WE", 3))
        return (ft_free(line), 1);
    else if (!ft_strncmp(line[0], "EA", 3))
        return (ft_free(line), 1);
    return (ft_free(line), 0);
}

int is_color(char *str)
{
    char **line = ft_split(str, ' ');
    if (!ft_strncmp(line[0], "F", 2))
        return (ft_free(line), 1);
    else if (!ft_strncmp(line[0], "C", 2))
        return (ft_free(line), 1);
    return (ft_free(line), 0);
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
    int i = 0;
    int len = ft_strlen(str);
    if (str[0] != '1' && str[len - 1] != '1')
        return (puts("error"), 0);
    while (str[i])
    {
        if (str[i] != '1' && str[i] != '0' && str[i] != 'N' && str[i] != 'E' && str[i] != 'S' && str[i] != 'W' && str[i] != ' ')
            return (0);
        ++i;
    }
    return (1);
}

char    **fill_map(char *str, char **map, int *height)
{
    char    **new_map;
    int     i;

    new_map = malloc(sizeof(char *) * ((*height) + 2));
    if (!new_map)
        return (NULL);
    i = 0;
    while (i < (*height))
    {
        new_map[i] = map[i];
        ++i;
    }
    ++(*height);
    new_map[i] = ft_strdup(str);
    new_map[++i] = NULL;
    free(map);
    return (new_map);
}

void    parse_map(char *str, t_info *info)
{
    if (valid_map(str))
        info->map = fill_map(str, info->map, &info->height);
}


void    parse_texter(char *str, t_info *info)
{
    char **line;

    line = ft_split(str, ' ');
    if (!line || !line[0] || !line[1])
    {
        ft_free(line);
        return ;
    }
    if (!ft_strncmp(line[0], "NO", 3) && !info->north)
        info->north = ft_strdup(line[1]);
    else if (!ft_strncmp(line[0], "SO", 3) && !info->south)
        info->south = ft_strdup(line[1]);
    else if (!ft_strncmp(line[0], "WE", 3) && !info->west)
        info->west = ft_strdup(line[1]);
    else if (!ft_strncmp(line[0], "EA", 3) && !info->east)
        info->east = ft_strdup(line[1]);
    else
    {
        printf("Error\n");
        ft_free(line);
        ft_clean(info);
        exit(1);
    }
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
    if (rgb[0] < 0 || rgb[1] < 0 || rgb[2] < 0)
        return (-1);
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
    if (get_color(line[1], info->cceiling) < 0 || get_color(line[1], info->cceiling) < 0)
    {
        printf("Invalid Values\n");
        ft_free(line);
        ft_clean(info);
        exit(1);
    }
    ft_free(line);
}

int check_map(t_info *info, int height)
{
    int i;

    while (info->map[height][i])
    {
        if (info->map[height][i] != '1' && info->map[height][i] != ' ')
            return (0);
        ++i;
    }
    return (1);
}
void    ft_clean(t_info *info)
{
    if (info->east)
        free(info->east);
    if (info->north)
        free(info->north);
    if (info->south)
        free(info->south);
    if (info->west)
        free(info->west);
    if (info->map)
        ft_free(info->map);
}

int dup_texter(char *texter, t_info *info)
{
    int count;

    count = 0;
    if (!ft_strncmp(texter, info->east, ft_strlen(texter)))
        ++count;
    if (!ft_strncmp(texter, info->north, ft_strlen(texter)))
        ++count;
    if (!ft_strncmp(texter, info->south, ft_strlen(texter)))
        ++count;
    if (!ft_strncmp(texter, info->west, ft_strlen(texter)))
        ++count;
    return (count == 1);
}

int check_texter(t_info *info)
{
    if (!dup_texter(info->east, info))
        return (0);
    else if (!dup_texter(info->north, info))
        return (0);
    else if (!dup_texter(info->south, info))
        return (0);
    else if (!dup_texter(info->west, info))
        return (0);
    return (1);
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
            return (free(line), ft_clean(info), 0);
        free(line);
    }
    close(fd);
    if (!check_map(info, 0) || !check_map(info, info->height - 1))
        return (ft_clean(info), 0);
    if (!check_texter(info))
        return (ft_clean(info), 0);
    return (1);
}


void ff()
{
    system("leaks cub");
}

int main(int ac, char **av)
{
    atexit(ff);
    t_info info;
    ft_memset(&info, 0, sizeof(t_info));
    if (!parsing("text.cub", &info))
        return (1);
    printf("%d\n%d\n%d\n", info.cfloor[0], info.cfloor[1], info.cfloor[2]);
    printf("%d\n%d\n%d\n", info.cceiling[0], info.cceiling[1], info.cceiling[2]);
    printf("%s\n%s\n%s\n%s\n", info.east, info.north, info.south, info.west);
    int i = 0;
    while (info.map[i])
    {
        printf("%s\n", info.map[i]);
        ++i;
    }
    ft_clean(&info);
    return (0);
}