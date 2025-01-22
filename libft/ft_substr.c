/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 21:12:51 by ptelo-de          #+#    #+#             */
/*   Updated: 2024/04/24 22:19:15 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	k;
	size_t	c;

	c = 0;
	if (!s)
		return (NULL);
	k = ft_strlen(s);
	if (start >= k)
		return (ft_strdup(""));
	else if (k <= (len + start))
		len = k - start;
	sub = ft_calloc((len + 1), sizeof(char));
	if (sub == NULL)
		return (NULL);
	while (s[start] && c < len)
	{
		sub[c] = s[start];
		start++;
		c++;
	}
	sub[c] = '\0';
	return (sub);
}

/* int main()
{
	s = ft_substr("tripouille", 100, 1);
	mcheck(s, 1); free(s);

} */