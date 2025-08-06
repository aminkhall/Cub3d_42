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

int	ft_atoi(const char *str)
{
	int		sign;
	long	num;

	sign = 1;
	num = 0;
    if (!is_valid(str))
        exit(EXIT_FAILURE);
	while (*str && ft_isdigit(*str))
	{
		num = num * 10 + (*str - '0');
        if (num > 255)
            exit(EXIT_FAILURE);
		str++;
	}
	return (num * sign);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!n)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && i < n - 1 && s1[i] && s2[i])
	{
		i++;
	}
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
