/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:39:03 by bde-luce          #+#    #+#             */
/*   Updated: 2025/03/28 20:39:06 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parsing.h"

size_t safe_strlen(const char *s)
{
	int i;

	if (!s) 
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);	
}

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

void restore_empty_str(void)
{
	t_token *tmp;
	t_token *next;

	tmp = get_shell()->tokens;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->type == QUOTE && (!tmp->str))
		{
			tmp->str = ft_calloc(1,1);
		}
		tmp = next;
	}
}

void clear_empty_token(void)
{
	t_shell *shell;
	t_token *tmp;
	t_token *next;

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

void update_str( char **update, char *src, int start, int len)
{
	char *aux;
	char *auxx;
	
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
