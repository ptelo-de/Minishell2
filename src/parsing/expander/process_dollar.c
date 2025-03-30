/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 01:48:57 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/03/30 00:30:26 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Retrieves the value of an environment variable.
 *
 * Searches the shell's environment list for the given variable `name`. 
 * If found, returns the value associated with the variable. If the value 
 * is empty, returns an empty string. If the variable doesn't exist, 
 * returns `NULL`.
 *
 * @param name Name of the environment variable to retrieve.
 *
 * @return The value of the environment variable, an empty string if the value 
 *         is empty, or `NULL` if the variable doesn't exist.
 *
 * Auxiliary functions: get_shell, ft_strncmp, ft_strlen.
 */
char	*get_value(char *name)
{
	t_list	*tmp;
	size_t	name_len;

	if (!name || !(get_shell()) || !(get_shell()->env))
	{
		return (NULL);
	}
	tmp = get_shell()->env;
	name_len = ft_strlen(name);
	while (tmp)
	{
		if (ft_strncmp(tmp->content, name, name_len) == 0 \
		&& ((char *)tmp->content)[name_len] == '=')
		{
			return ((char *)tmp->content + name_len + 1);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

/**
 * @brief Expands the exit status into the provided string.
 *
 * Converts the shell's exit status to a string and appends it to the 
 * `update` string. If the `exit_status` is successfully converted, it 
 * is added to `update`. The temporary string used for the conversion 
 * is freed after use.
 *
 * @param update Pointer to the string being updated with the exit status.
 *
 * @return void.
 *
 * Auxiliary functions: ft_itoa, update_str, free.
 */
void	exit_status_expander( char **update)
{
	char	*aux;

	aux = ft_itoa(get_shell()->exit_status);
	update_str(update, aux, 0, safe_strlen(aux));
	if (aux)
		free(aux);
}

/**
 * @brief Expands a standard dollar sign format variable (`$variable`).
 *
 * Extracts the variable name following a dollar sign (`$`) in the source 
 * string `src`, retrieves its value, and appends it to the `update` string. 
 * The length pointer (`len_pointer`) is updated based on the length of the 
 * expanded value. If the variable exists and has a non-empty value, 
 * it is appended to `update`; otherwise, no changes are made.
 *
 * @param pointer_add Pointer to the length pointer which tracks the 
 *                    processed characters in `src`.
 * @param src The source string containing the dollar sign and variable.
 * @param update The string being updated with the expanded value.
 *
 * @return void.
 *
 * Auxiliary functions: ft_isalnum, ft_substr, get_value, ft_strdup, 
 *                     ms_strjoin, free.
 */
void	expand_standard_dollar_format(int **pointer_add, \
char *src, char **update)
{
	int		i;
	char	*var_name;
	char	*value;
	char	*aux;
	int		*len_pointer;

	i = 1;
	len_pointer = *pointer_add;
	while (ft_isalnum(src[i]) || src[i] == '_')
		i++;
	i--;
	var_name = ft_substr(src, 1, i);
	value = get_value(var_name);
	if (value && value[0])
	{
		aux = ft_strdup(*update);
		if (*update)
			free(*update);
		*update = ms_strjoin(aux, value);
		if (aux)
			free(aux);
	}
	*len_pointer = *len_pointer + i + 1;
	if (var_name)
		free(var_name);
}

/**
 * @brief Processes a dollar sign (`$`) for variable expansion in the string.
 *
 * Depending on the character following the dollar sign in `src`, this function 
 * handles different cases: 
 * - If the next character is a quote (`"`, `'`), it just skips over it.
 * - If the next character is not a valid variable name or `?`, it appends 
 *   the `$` and the next character to `update`.
 * - If the next character is `?`, it expands the exit status into `update`.
 * - Otherwise, it processes the dollar sign followed by a valid variable name.
 * The length pointer `len` is updated accordingly based 
 * on the processed characters.
 *
 * @param len Pointer to the length of the processed characters in `src`.
 * @param src Source string which starts with dollar sign.
 * @param update The string being updated with the expanded value.
 *
 * @return void.
 *
 * Auxiliary functions: ft_isalpha, update_str, exit_status_expander, 
 *                     expand_standard_dollar_format.
 */
void	process_dollar(int *len, char *src, char **update)
{
	if (src[1] == '\"' || src[1] == '\'')
	{
		(*len)++;
		return ;
	}
	if (!ft_isalpha(src[1]) && src[1] != '_' && src[1] != '?')
	{
		update_str(update, src, 0, 2);
		if (src[1] == '\0')
			(*len)++;
		else
			*len += 2;
	}
	else if (src[1] == '?')
	{
		exit_status_expander(update);
		*len += 2;
	}
	else
		expand_standard_dollar_format(&len, src, update);
}
