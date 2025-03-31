/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:36:30 by bde-luce          #+#    #+#             */
/*   Updated: 2025/03/31 13:58:48 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "executer.h"
#include "minishell.h"

//fucntion that sets shlvl whenever the minishell is called

static char	*set_shlvl(char *shlvl_value)
{
	int		shlvl;
	char	*increased_shlvl;
	char	*updated_shlvl;

	shlvl = ft_atoi(shlvl_value);
	shlvl++;
	increased_shlvl = ft_itoa(shlvl);
	updated_shlvl = ft_strjoin("SHLVL=", increased_shlvl);
	free(increased_shlvl);
	return (updated_shlvl);
}

//function that generates env from envp

t_list	*get_env(char **envp)
{
	t_list	*env;
	int		i;
	char	*dup;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
			dup = set_shlvl(getenv("SHLVL"));
		else
			dup = ft_strdup(envp[i]);
		if (!dup)
		{
			free_lst(env);
			return (NULL);
		}
		ft_lstadd_back(&env, ft_lstnew(dup));
		i++;
	}
	if (!getenv("SHLVL"))
		ft_lstadd_back(&env, ft_lstnew(ft_strdup("SHLVL=1")));
	return (env);
}
