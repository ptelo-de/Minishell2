/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:51:39 by bde-luce          #+#    #+#             */
/*   Updated: 2025/04/03 19:25:51 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "executer.h"

/**
 * @brief Starts and runs the minishell program.
 *
 * Sets up the shell environment and runs an infinite loop that:
 * - reads user input,
 * - parses and validates it,
 * - expands variables,
 * - executes commands,
 * - and cleans up after each cycle.
 *
 * @param argc number of command-line arguments.
 * @param argv command-line arguments (unused).
 * @param envp environment variables.
 * 
 * @return never returns (infinite loop).
 */
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
			close_all_fd_red();
		}
		free_atributes();
		free(shell->readline);
		shell->readline = NULL;
	}
	free_all();
}
