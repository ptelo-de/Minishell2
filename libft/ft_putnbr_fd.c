/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 21:05:06 by ptelo-de          #+#    #+#             */
/*   Updated: 2024/04/14 10:54:12 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	j;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		j = (long)(n);
		j *= -1;
	}
	else
		j = (long)n;
	if (j <= 9)
		ft_putchar_fd(j + 48, fd);
	else
	{
		ft_putnbr_fd(j / 10, fd);
		ft_putnbr_fd(j % 10, fd);
	}
}
/* int main()
{
	ft_putnbr_fd(-2147483648, 1);
} */