/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 20:13:52 by mkhallou          #+#    #+#             */
/*   Updated: 2025/08/08 20:13:53 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int is_color(char *str)
{
    char **line = ft_split(str, ' ');
    if (!ft_strncmp(line[0], "F", 2))
        return (ft_free(line), 1);
    else if (!ft_strncmp(line[0], "C", 2))
        return (ft_free(line), 1);
    return (ft_free(line), 0);
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
