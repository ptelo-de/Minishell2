/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 21:07:55 by ptelo-de          #+#    #+#             */
/*   Updated: 2024/04/17 21:45:38 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	lsrc;
	size_t	ldst;

	if ((!dst || !src) && !size)
		return (0);
	ldst = ft_strlen(dst);
	lsrc = ft_strlen(src);
	i = 0;
	if (size <= ldst)
		return (size + lsrc);
	else
	{
		while (i < (size - ldst - 1) && src[i])
		{
			dst[ldst + i] = src[i];
			i++;
		}
		dst[ldst + i] = '\0';
		return (ldst + lsrc);
	}
}
/* #include <string.h>

int	main(void)
{
	char	*dest;

	alarm(5);
	if (!(dest = (char *)malloc(sizeof(*dest) * 15)))
		return (0);
	memset(dest, 0, 15);
	memset(dest, 'r', 14);
	//printf("%s\n", dest);
		printf("%zu",ft_strlcat(dest, "lorem ipsum dolor sit amet", 15));
} */