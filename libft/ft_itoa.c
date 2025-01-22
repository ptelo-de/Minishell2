/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:22:40 by ptelo-de          #+#    #+#             */
/*   Updated: 2024/04/21 18:24:49 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countchr(long n)
{
	size_t	rl;

	rl = 1;
	if (!n)
		return (1);
	if (n > 0)
	{
		while (n > 9)
		{
			rl++;
			n = n / 10;
		}
	}
	else
	{
		rl++;
		n = -n;
		while (n > 9)
		{
			rl++;
			n = n / 10;
		}
	}
	return (rl);
}

char	*ft_itoa(int n)
{
	char		*r;
	size_t		rl;
	size_t		i;
	long int	n2;

	rl = ft_countchr(n);
	i = 0;
	n2 = n;
	r = (char *)ft_calloc(rl + 1, sizeof(char));
	if (!r)
		return (NULL);
	if (n2 < 0)
	{
		r[i] = '-';
		i++;
		n2 = -n2;
	}
	r[rl] = '\0';
	while (--rl > i)
	{
		r[rl] = (48 + n2 % 10);
		n2 /= 10;
	}
	r[i] = 48 + n2 % 10;
	return (r);
}
/* int main()
{
			char	*i1 = ft_itoa(-2147483648);
			char	*i2 = ft_itoa(1031797530);
			char	*i3 = ft_itoa(1234);

			printf("%s\n%s\n%s\n",i1,i2,i3);
			ft_bzero(i1, ft_strlen(i1)*sizeof(char));
			free(i1);
			ft_bzero(i2, ft_strlen(i2)*sizeof(char));
			free(i2);
			ft_bzero(i3, ft_strlen(i3)*sizeof(char));
			free(i3);
			//tested with valgrind
} */