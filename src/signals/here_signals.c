/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:57:15 by bde-luce          #+#    #+#             */
/*   Updated: 2025/03/31 19:18:52 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"
#include "parsing.h"

void	here_sigint_handler(int signum)
{
	t_shell	*shell;

	shell = get_shell();
	(void)signum;
	write(1, "\n", 1);
	close(shell->here_pipe[1]);
	close_all_fd_red();
	shell->exit_status = 130;
	ms_exit(&shell, NULL);
}

void	here_sigint(void)
{
	struct sigaction	sa;
	t_shell				*shell;

	shell = get_shell();
	sa.sa_handler = here_sigint_handler;
	sa.sa_flags = SA_RESTART;
	if (sigemptyset(&sa.sa_mask) || sigaction(SIGINT, &sa, NULL))
	{
		write(2, "sigaction failed at interactive mode in SIGINT\n", 48);
		ms_exit(&shell, NULL);
	}
}
