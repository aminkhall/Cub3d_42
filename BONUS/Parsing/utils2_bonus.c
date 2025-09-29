/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallou <mkhallou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:41:18 by mkhallou          #+#    #+#             */
/*   Updated: 2025/09/29 19:04:12 by mkhallou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = ft_strlen((char *)src);
	if (dstsize <= 0)
		return (i);
	while (*src && --dstsize)
		*dst++ = *src++;
	*dst = '\0';
	return (i);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	n;
	unsigned char	*s;

	n = (unsigned char)c;
	s = (unsigned char *)b;
	while (len--)
		*s++ = n;
	return (b);
}

void	ft_clean(t_info *info)
{
	if (!info)
		return ;
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

void	error_handler(char *str, t_info *info)
{
	printf("%s\n", str);
	ft_clean(info);
	close(info->fd);
	exit(1);
}
