#include "../cub3d_bonus.h"

int is_door(char *str)
{
    char **line;

    if (!str)
        return (0);
    line = ft_split(str, ' ');
    if (!line)
        return (0);
    if (!ft_strncmp("DO", line[0], 3))
        return (ft_free(line), 1);
    return (0);
}

void    parse_door(char *str, t_info *info)
{
    char **line;

    if (!str)
        return ;
    line = ft_split(str, ' ');
    if (!line || !line[0] || !line[1] || line[2])
	{
		error_handler("Texter Invalid", info);
		ft_free(line);
	}
    else if (!ft_strncmp("DO", line[0], 3))
        info->door = ft_strdup(line[1]);
    ft_free(line);
    return ;
}