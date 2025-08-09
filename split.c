#include "cub.h"

static int	ft_strlen_sep(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	ft_count_word(char const *s, char c)
{
	int	count;
	int	in;

	count = 0;
	in = 0;
	if (!*s)
		return (0);
	if (s[0] != c)
		count++;
	while (*s)
	{
		if (*s == c)
			in = 1;
		else if (in)
		{
			count++;
			in = 0;
		}
		s++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	int		count_word;
	char	**tab;
	int		i;
	int		len;

	if (!s)
		return (NULL);
	count_word = ft_count_word(s, c);
	tab = (char **)malloc(sizeof(char *) * (count_word + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < count_word)
	{
		while (*s == c && *s)
			s++;
		len = ft_strlen_sep(s, c);
		tab[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!tab[i])
			return (ft_free(tab), NULL);
		ft_strlcpy(tab[i++], s, len + 1);
		s += len;
	}
	tab[count_word] = 0;
	return (tab);
}
