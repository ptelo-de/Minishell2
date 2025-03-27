#include "minishell.h"

t_redir **get_red(t_token	*token)
{
    int	redir_num;
    int	i;
	t_token	*tmp;
	t_redir **red;

	redir_num = 0;
	tmp = token;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == REDIR)
			redir_num++;
		tmp = tmp->next;
	}
	red = ft_calloc(sizeof(t_redir *), redir_num + 1);
	if (!red)
		return ( NULL);
	i = 0;
	while (i < redir_num)
	{
		(red)[i] = ft_calloc(sizeof(t_redir), 1);
		if (!(red)[i])
			return ( NULL);
		i++;
	}
	i = 0;
	tmp = token;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == REDIR)
		{
			red[i]->type = tmp->next->type;
			red[i]->str = tmp->next->str;
			if (ft_strncmp(tmp->str, "<<", 2) == 0)
				red[i++]->type = HERE_DOC;
			else if (!ft_strncmp(tmp->str, ">>", 2))
				red[i++]->type = APPEND;
			else if (!ft_strncmp(tmp->str, ">", 2))
				red[i++]->type = OUTFILE;
			else
				red[i++]->type = INFILE;
		}
		tmp = tmp->next;
	}
	red[i] = NULL;
	return (red);
}
int	is_arg(t_token *token)
{
	if ((token->type == WORD || token->type == QUOTE || token->type == DOLLAR) \
	&& (!token->prev || token->prev->type != REDIR))
	{
		return 1;
	}
	return 0;
}
void	get_args(t_token *token, t_cmd *cmd)
{
	t_token *tmp;
	int arg_num;
	int i;

	tmp = token;
	arg_num = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (is_arg(tmp))
			arg_num++;
		tmp = tmp->next;
	}
	cmd->arg = ft_calloc(sizeof(char*) * (arg_num + 1), 1);
	if (!(cmd->arg))
		return;
	i = 0;
	tmp = token;
	while (tmp && tmp->type != PIPE)
	{
		if (is_arg(tmp))
			(cmd->arg)[i++] = tmp->str;
		tmp = tmp->next; 
	}
	(cmd->arg)[i] = NULL;
	cmd->n_arg = arg_num;
}

void get_next_cmd_token(t_token **token)
{
	while(*token && (*token)->type != PIPE)
		*token = (*token)->next;
	if (*token)
		(*token) = (*token)->next;
}
t_cmd *get_cmd(t_token *token)
{
    t_cmd *cmd;

    cmd = ft_calloc(sizeof(t_cmd), 1);
    if (cmd == NULL)
    {
        return(NULL);
    }
	cmd->pid = 0;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
    get_args(token, cmd);
    if (!cmd->arg)
    {
        return(NULL);
    }
    cmd->red= get_red(token);
    return (cmd);
}
int init_cmd(void)
{
    int     cmd_num;
    t_token *tmp;
    int     i;

    tmp = get_shell()->tokens;
    cmd_num = 1;
    while(tmp != NULL)
    {
        if (tmp->type == PIPE)
            cmd_num++;
		tmp = tmp->next;
    }
    get_shell()->cmd = ft_calloc(sizeof(t_cmd *) * (cmd_num + 1), 1);
    if (get_shell()->cmd == NULL)
        return(1);
    tmp = get_shell()->tokens;
	get_shell()->cmd[0] = get_cmd(tmp);
    i = 1;
    while(i < cmd_num)
    {
		get_next_cmd_token(&tmp);
        get_shell()->cmd[i++] = get_cmd(tmp);
    }
	get_shell()->cmd[i] = NULL;
    return (0);
}
