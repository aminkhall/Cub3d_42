#include "cub.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int is_valid(char *str)
{
    int i;

    if (!str)
        return (0);
    i = 0;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        ++i;
    }
    return (1);
}

int	ft_atoi(char *str)
{
	int		sign;
	long	num;

	sign = 1;
	num = 0;
    if (!is_valid(str))
        return (-1);
	while (*str && ft_isdigit(*str))
	{
		num = num * 10 + (*str - '0');
        if (num > 255)
            return (-1);
		str++;
	}
	return (num * sign);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	if (!n)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

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

	i = ft_strlen(src);
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

	n = (unsigned char) c;
	s = (unsigned char *) b;
	while (len--)
		*s++ = n;
	return (b);
}