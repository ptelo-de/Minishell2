/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:21:59 by ptelo-de          #+#    #+#             */
/*   Updated: 2024/04/24 22:17:46 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	occ;
	size_t	i;

	i = 0;
	occ = 0;
	while (s[i])
	{
		if (s[i] != c && s[i])
		{
			occ++;
			while (s[i] && s[i] != c)
				i++;
			if (!s[i])
				break ;
		}
		i++;
	}
	return (occ);
}

static void	ft_free(char **r, int j)
{
	while (j > 0)
	{
		free(r[--j]);
	}
	free(r);
}

static char	**ft_writewords(char **r, char const *s, char c)
{
	int	i;
	int	k;
	int	j;

	i = 0;
	k = 0;
	while (k < (int)ft_count_words(s, c))
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
		{
			j = 0;
			while (s[i + j] && s[i + j] != c)
				j++;
			r[k] = ft_substr(s, i, j);
			if (!r[k++])
			{
				ft_free(r, k);
				return (NULL);
			}
			i += j;
		}
		i++;
	}
	r[k] = NULL;
	return (r);
}

char	**ft_split(char const *s, char c)
{
	char	**r;

	if (!(s))
		return (NULL);
	r = ft_calloc((ft_count_words(s, c) + 1), sizeof(char *));
	if (!r)
		return (NULL);
	r = ft_writewords(r, s, c);
	if (!r)
		return (NULL);
	return (r);
}
/* int main()
{
	char **tab = ft_split("", ' ');
	printf("%s\n", tab[100]);
	ft_free(tab, 1);
int		main(void)
{
	char s[] = "St ge da pa cm ct ws!";

	printf("%zu\n", ft_count_words(s, ' '));
	char **r = ft_split(s, 32);
	//(void)r;
	int i = 0;
	while (i < 8)//(int)ft_count_words(s, ' ') + 1)
	{
		printf("%s\n", r[i]);
		i++;
	}
	ft_free(r, 7);

	return (0);

} */
