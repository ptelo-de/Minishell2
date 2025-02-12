#include "minishell.h"

t_redir **get_red(t_token	*token, int	here_flag)
{
    int	redir_num;
    int	i;
	t_token	*tmp;
	t_redir **red;

	redir_num = 0;
	tmp = token;
	while (tmp && tmp->type != PIPE)
	{
		if (here_flag && tmp->type == REDIR && ft_strncmp(tmp->str, "<<", 2) == 0)
			redir_num++;
		if (!here_flag && tmp->type == REDIR && ft_strncmp(tmp->str, "<<", 2) != 0)
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
		if (here_flag && tmp->type == REDIR && ft_strncmp(tmp->str, "<<", 2) == 0)
		{
			red[i]->str = tmp->next->str;
			red[i++]->type = HERE_DOC;
		}
		if (!here_flag && tmp->type == REDIR && ft_strncmp(tmp->str, "<<", 2))
		{
			red[i]->str = tmp->next->str;
			if (!ft_strncmp(tmp->str, ">>", 2))
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
void	get_args(t_token *token, t_cmd *cmd)
{
	t_token *tmp;
	int arg_num;
	int i;

	tmp = token;
	arg_num = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD && (!tmp->prev || tmp->prev->type != REDIR))
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
		if (tmp->type == WORD && (!tmp->prev || tmp->prev->type != REDIR))
			(cmd->arg)[i++] = tmp->str;
		tmp = tmp->next; 
	}
	(cmd->arg)[i] = NULL;
	cmd->n_arg = arg_num;
}

t_cmd *get_cmd(t_token *token)
{
    t_cmd *cmd;

    cmd = ft_calloc(sizeof(t_cmd), 1);
    if (cmd == NULL)
    {
        return(NULL);
    }
    get_args(token, cmd);
    if (!cmd->arg)
    {
        return(NULL);
    }
    cmd->red= get_red(token, 0);
	cmd->here = get_red(token, 1);
    return (cmd);
}
void get_next_cmd_token(t_token **token)
{
	while(*token && (*token)->type != PIPE)
		*token = (*token)->next;
	if (*token)
		(*token) = (*token)->next;
}
int init_cmd(void)
{
    t_shell *shell;
    int     cmd_num;
    t_token *tmp;
    int     i;

    shell = get_shell();
    tmp = shell->tokens;
    cmd_num = 1;
    while(tmp != NULL)
    {
        if (tmp->type == PIPE)
            cmd_num++;
		tmp = tmp->next;
    }
    shell->cmd = ft_calloc(sizeof(t_cmd *) * (cmd_num + 1), 1);
    if (shell->cmd == NULL)
        return(1);
    tmp = shell->tokens;
	shell->cmd[0] = get_cmd(tmp);
    i = 1;
    while(i < cmd_num)
    {
		get_next_cmd_token(&tmp);
        shell->cmd[i] = get_cmd(tmp);
		i++;
    }
	shell->cmd[i] = NULL;
    return (0);
}
