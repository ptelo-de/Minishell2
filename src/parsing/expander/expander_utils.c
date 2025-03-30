/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 01:58:15 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/03/30 00:19:01 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Safely calculates the length of a string.
 *
 * Computes the length of the given string `s`, ensuring that a `NULL` 
 * input returns `0` instead of causing undefined behavior. 
 *
 * @param s Pointer to the string whose length is to be determined.
 *
 * @return The length of the string `s` as a `size_t` value. 
 *         Returns `0` if `s` is `NULL`.
 */
size_t	safe_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

/**
 * @brief Safely concatenates two strings.
 *
 * Allocates and returns a new string that is the result of concatenating 
 * `s1` and `s2`. If either string is `NULL`, it is treated as an empty string.
 * The function ensures memory allocation for the new string, including 
 * the null terminator.
 *
 * Auxiliar functions: malloc, safe_strlen.
 * @param s1 First string to concatenate.
 * @param s2 Second string to concatenate.
 *
 * @return A newly allocated string containing `s1` followed by `s2`. 
 *         Returns `NULL` if memory allocation fails.
 */
char	*ms_strjoin(const char *s1, const char *s2)
{
	char	*join;
	size_t	i;
	size_t	j;

	join = malloc((safe_strlen(s1) \
			+ safe_strlen(s2) + 1) * (sizeof(char)));
	if (join == 0)
		return (0);
	i = 0;
	while (s1 && s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = 0;
	return (join);
}

/**
 * @brief Restores empty strings for quoted tokens.
 *
 * Iterates through the shell's token list and ensures that any token of 
 * type `QUOTE` with a `NULL` string is replaced with an allocated empty 
 * string (`""`). This prevents potential issues with null string references 
 * in further processing.
 *
 * @return void.
 *
 * Auxiliary functions: get_shell, ft_calloc.
 */
void	restore_empty_str(void)
{
	t_token	*tmp;
	t_token	*next;

	tmp = get_shell()->tokens;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->type == QUOTE && (!tmp->str))
		{
			tmp->str = ft_calloc(1, 1);
		}
		tmp = next;
	}
}

/**
 * @brief Removes empty tokens of type DOLLAR from the shell's token list.
 *
 * Iterates through the token list and removes any token of type `DOLLAR` 
 * that has a `NULL` or empty string. Properly updates the linked list 
 * pointers to maintain list integrity after removal. Calls 
 * `restore_empty_str()` to ensure empty quoted tokens are handled.
 *
 * @return void.
 *
 * Auxiliary functions: get_shell, restore_empty_str, free.
 */
void	clear_empty_token(void)
{
	t_shell	*shell;
	t_token	*tmp;
	t_token	*next;

	shell = get_shell();
	tmp = shell->tokens;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->type == DOLLAR && (!tmp->str || !tmp->str[0]))
		{
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			else
				shell->tokens = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			free(tmp);
		}
		tmp = next;
	}
	restore_empty_str();
}

/**
 * @brief Updates a string by appending a substring from the source.
 *
 * Extracts a substring from `src`, starting at `start` with length `len`, 
 * and appends it to the `update` string. The previous value of `update` 
 * is freed before assigning the new concatenated result.
 *
 * @param update Pointer to the string being updated.
 * @param src Source string from which the substring is extracted.
 * @param start Starting index of the substring in `src`.
 * @param len Length of the substring to extract.
 *
 * @return void.
 *
 * Auxiliary functions: ft_substr, ft_strdup, ms_strjoin, free.
 */
void	update_str( char **update, char *src, int start, int len)
{
	char	*aux;
	char	*auxx;

	auxx = ft_substr(src, start, len);
	aux = ft_strdup(*update);
	if (*update)
		free(*update);
	*update = ms_strjoin(aux, auxx);
	if (aux)
		free(aux);
	if (auxx)
		free(auxx);
}
