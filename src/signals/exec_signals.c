/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:53:03 by bde-luce          #+#    #+#             */
/*   Updated: 2025/03/25 13:31:39 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_handler(int signal)
{
	t_shell *shell;
	
    shell = get_shell();    
	if (signal == SIGQUIT)
	{
		shell->exit_status = 131;
		//write(1, "\n", 1);
	}
	if (signal == SIGINT)
	{
		shell->exit_status = 130;
		//write(1, "\n", 1);
	}
}

void exec_mode(void)
{
	struct sigaction sa;

	sa.sa_handler = exec_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL))
	{
		perror("sigaction failed at execution mode in SIGINT");
		//free all minishell memory
		exit(1);
	}
	if (sigaction(SIGQUIT, &sa, NULL))
	{
		perror("sigaction failed at execution mode in SIGQUIT");
		//free all minishell memory
		exit(1);
	}
}
