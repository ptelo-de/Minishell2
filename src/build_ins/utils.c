/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:10:53 by bde-luce          #+#    #+#             */
/*   Updated: 2025/04/03 16:50:40 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "executer.h"
#include "minishell.h"

/**
 * @brief Frees a null-terminated array of strings.
 *
 * Iterates through the array, freeing each string and then
 * frees the array itself. Safely handles NULL input.
 *
 * @param arr the array of strings to free.
 * 
 * @return void.
 */
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

/**
 * @brief Removes a given prefix from a string, if present.
 *
 * If the string starts with the specified prefix, returns a new string
 * with the prefix removed. Otherwise, returns a full copy of the original string.
 *
 * @param str the original string.
 * @param prefix the prefix to remove.
 * 
 * @return a newly allocated string without the prefix if it was present,
 * or a full copy of the original string if not. Returns NULL on allocation failure.
 */
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

/**
 * @brief Returns the length of the longer of two strings.
 *
 * Compares the lengths of `str1` and `str2` and returns the greater one.
 *
 * @param str1 the first string.
 * @param str2 the second string.
 * 
 * @return the length of the longer string.
 */
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

/**
 * @brief Returns the length of a null-terminated array of strings.
 *
 * Counts how many strings exist in the array.
 *
 * @param arr the array to measure.
 * 
 * @return the number of elements in the array.
 */
int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

/**
 * @brief Prints a message and returns the given exit status.
 *
 * Utility function to simplify error reporting and returning status codes.
 *
 * @param message the message to print.
 * @param exit_status the status code to return.
 * 
 * @return the provided exit status.
 */
int	print_and_return(char *message, int exit_status)
{
	printf("%s\n", message);
	return (exit_status);
}
