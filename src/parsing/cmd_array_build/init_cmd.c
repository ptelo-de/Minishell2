/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 02:04:54 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/04/01 19:04:55 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

t_cmd	*get_next_cmd(t_token *token)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (cmd == NULL)
	{
		return (NULL);
	}
	cmd->pid = 0;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->out_error = 0;
	get_args(token, cmd);
	if (!cmd->arg)
	{
		return (NULL);
	}
	cmd->red = get_red(token);
	return (cmd);
}

void	get_next_cmd_token(t_token **token)
{
	while (*token && (*token)->type != PIPE)
		*token = (*token)->next;
	if (*token)
		(*token) = (*token)->next;
}

int	count_cmds(t_token	*tokens)
{
	int	cmd_num;

	cmd_num = 1;
	while (tokens != NULL)
	{
		if (tokens->type == PIPE)
			cmd_num++;
		tokens = tokens->next;
	}
	return (cmd_num);
}

int	init_cmd(void)
{
	int		cmd_num;
	t_token	*tmp;
	int		i;
	size_t	size_p;

	cmd_num = count_cmds(get_shell()->tokens);
	size_p = sizeof(t_cmd *);
	get_shell()->cmd = ft_calloc(cmd_num + 1, size_p);
	if (get_shell()->cmd == NULL)
		return (1);
	tmp = get_shell()->tokens;
	get_shell()->cmd[0] = get_next_cmd(tmp);
	i = 1;
	while (i < cmd_num)
	{
		get_next_cmd_token(&tmp);
		get_shell()->cmd[i++] = get_next_cmd(tmp);
	}
	get_shell()->cmd[i] = NULL;
	return (0);
}
