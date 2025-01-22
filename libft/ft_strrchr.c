/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 21:11:06 by ptelo-de          #+#    #+#             */
/*   Updated: 2024/04/24 22:18:58 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	l;

	l = ft_strlen(s);
	if ((unsigned char)c == '\0')
		return ((char *)(s + (int)(ft_strlen(s))));
	while (l >= 0)
	{
		if (s[l] == (unsigned char)c)
			return ((char *)s + l);
		l--;
	}
	return (0);
}
