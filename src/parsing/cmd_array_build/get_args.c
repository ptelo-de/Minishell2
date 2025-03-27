#include "minishell.h"
#include "parsing.h"

int	is_arg(t_token *token)
{
	if ((token->type == WORD || \
	token->type == QUOTE || token->type == DOLLAR) \
	&& (!token->prev || token->prev->type != REDIR))
	{
		return 1;
	}
	return 0;
}

void	assign_args(t_token	*tokens, char	***args)
{
	int	i;

	i = 0;
	while (tokens && tokens->type != PIPE)
	{
	if (is_arg(tokens))
		(*args)[i++] = tokens->str;
	tokens = tokens->next; 
	}
	(*args)[i] = NULL;
}

void	get_args(t_token *token, t_cmd *cmd)
{
	t_token *tmp;
	int arg_num;

	tmp = token;
	arg_num = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (is_arg(tmp))
			arg_num++;
		tmp = tmp->next;
	}
	cmd->arg = ft_calloc(sizeof(char*) \
				* (arg_num + 1), 1);
	if (!(cmd->arg))
		return;
	assign_args(token, &cmd->arg);
	cmd->n_arg = arg_num;
}
