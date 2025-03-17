/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:58:34 by ptelo-de          #+#    #+#             */
/*   Updated: 2024/04/17 19:24:42 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

/*
 #include "libft.h"
 #include <stdlib.h>
 #include <string.h>
 #include <unistd.h>
 void	iter(unsigned int i, char *c)
 {
		static int indexArray[11] = {0};

		if (i > 10 || indexArray[i] == 1)
			write(1, "wrong index\n", 12);
		else
			indexArray[i] = 1;
		if (*c >= 'a' && *c <= 'z')
			*c = *c - 32;
		else if (*c >= 'A' && *c <= 'Z')
			*c = *c + 32;
 }

 int		main(int argc, const char *argv[])
 {
		char	*str;
		str = (char *)malloc(sizeof(*str) * 12);
			strcpy(str, "LoReM iPsUm");
			printf("%s\n",str);
			ft_striteri(str, &iter);
			printf("%s\n",str);
		return (0);
 } */