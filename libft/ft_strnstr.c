/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 21:10:51 by ptelo-de          #+#    #+#             */
/*   Updated: 2024/04/22 17:40:00 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*big;
	char	*little;
	size_t	c;
	size_t	i;

	if (!len && !haystack)
		return (NULL);
	if (!needle[0])
		return ((char *)haystack);
	big = (char *)haystack;
	little = (char *)needle;
	i = 0;
	while (i < len && haystack[i])
	{
		c = 0;
		while (i + c < len && big[i + c] == little[c])
		{
			if (little[c + 1] == '\0')
				return (big + i);
			c++;
		}
		i++;
	}
	return (NULL);
}
/* int main(void)
{
	printf("%s\n",ft_strnstr("lorem ipsum dolor sit amet", "", 10));
	printf("%s\n",ft_strnstr("lorem ipsum dolor sit amet", "dol", 30));
} */