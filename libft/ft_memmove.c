/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 21:05:33 by ptelo-de          #+#    #+#             */
/*   Updated: 2024/04/19 23:49:02 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	if ((size_t)dest - (size_t)src < n)
	{
		i = (int)n - 1;
		while (i >= 0)
		{
			((unsigned char *)(dest))[i] = ((unsigned char *)(src))[i];
			i--;
		}
	}
	else
	{
		while (i < (int)n)
		{
			((unsigned char *)(dest))[i] = ((unsigned char *)(src))[i];
			i++;
		}
	}
	return (dest);
}
/* #include <string.h>
int	main(void)
{
			char	*src = "thanks to @apellicc for this test !\r\n";
			char	dst1[0xF0];
			char *dst2 = "" - 1;
			char *dst3 = "";
			int		size = strlen(src);
			//printf("src: %p\n dst1: %p\ndst2:%p\ndst3%p\n%s", src,
				dst1,dst2,dst3,dst2);

			char	*r1 = memmove(dst1, src, size);
			char	*r2 = ft_memmove(dst1, src, size);
			r1 = memmove("", dst2, 0);
			printf("%s",dst2);
			r2 = ft_memmove("", "" - 1, 0);
} */