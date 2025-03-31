/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:51:39 by bde-luce          #+#    #+#             */
/*   Updated: 2025/03/31 19:14:42 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "executer.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	*shell;

	(void)argv;
	shell = get_shell();
	check_main_args(argc);
	shell->env = get_env(envp);
	shell->exp = get_exp(make_env_arr(shell->env));
	while (1)
	{
		interactive_mode();
		if (lexer() == 1 || syntax_check() == 1)
			free_atributes();
		else
		{
			expander();
			(void)init_cmd();
			shell->exit_status = 0;
			executer(shell);
		}
		free_atributes();
		free(shell->readline);
		shell->readline = NULL;
	}
	free_lst(shell->env);
	free_lst(shell->exp);
}
