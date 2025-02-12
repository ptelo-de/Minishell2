/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 21:06:59 by ptelo-de          #+#    #+#             */
/*   Updated: 2024/04/22 16:46:42 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;
	size_t	max;

	max = nmemb * size;
	if (nmemb && size && max / size != nmemb)
		return (NULL);
	array = malloc(max);
	if (!array)
		return (NULL);
	ft_bzero(array, max);
	return (array);
}
