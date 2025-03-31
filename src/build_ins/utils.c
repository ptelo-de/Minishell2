/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:10:53 by bde-luce          #+#    #+#             */
/*   Updated: 2025/03/31 19:31:12 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "executer.h"
#include "minishell.h"

//function that frees an array

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

//function that trims a prefix from a string

char	*trim_prefix(char *str, char *prefix)
{
	size_t	start;
	char	*trim;

	start = 0;
	if (ft_strncmp(str, prefix, ft_strlen(prefix)) == 0)
		start += ft_strlen(prefix);
	trim = ft_substr(str, start, ft_strlen(str) - start);
	if (!trim)
		return (NULL);
	return (trim);
}

//function that returns the length of the longest of 2 strings

int	is_longer(char	*str1, char	*str2)
{
	int	l1;
	int	l2;

	l1 = ft_strlen(str1);
	l2 = ft_strlen(str2);
	if (l1 > l2)
		return (l1);
	return (l2);
}

//function that returns the length of an array of strings

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

//function that prints a message and returns an exit status

int	print_and_return(char *message, int exit_status)
{
	printf("%s\n", message);
	return (exit_status);
}
