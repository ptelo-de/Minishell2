#include "minishell.h"

t_redir **get_red(t_token	*token, int	in_flag)
{
    int	redir_num;
    int	i;
	t_token	*tmp;
	t_redir **red;

	redir_num = 0;
	tmp = token;
	while (tmp && tmp->type != PIPE)
	{
		if (in_flag && tmp->type == REDIR && ft_strncmp(tmp->str, "<", 1) == 0)
			redir_num++;
		if (!in_flag && tmp->type == REDIR && ft_strncmp(tmp->str, ">", 1) == 0)
			redir_num++;
		tmp = tmp->next;
	}
//	printf("redir _num: %d\n", redir_num);
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
		if (in_flag && tmp->type == REDIR && ft_strncmp(tmp->str, "<", 1) == 0)
		{
			//printf("(1get red: antes da segfault\n"); 
			red[i]->str = tmp->next->str; //need seg fault protection
			//printf("1red file: %s\n", red[i]->str);
			if (ft_strlen(tmp->str) == 2)
			{
				//printf("Estou no if ft_strlen\n");
				red[i++]->type = HERE_DOC;
			}
			else
				red[i++]->type = INFILE;
			//printf("(2get red: antes da segfault\n"); 
		}
		if (!in_flag && tmp->type == REDIR && ft_strncmp(tmp->str, ">", 1) == 0)
		{
			red[i]->str = tmp->next->str;
			if (ft_strlen(tmp->str) == 2)
				red[i++]->type = APPEND;
			else
				red[i++]->type = OUTFILE;
		}
		tmp = tmp->next;
	}
	red[i] = NULL;
	//printf("3get red: antes da segfault\n"); 
/*	i = 0 ;   
	while (red[i])
	{
		printf("redir %d: %s\n", i, red[i]->str);
		i++;

	}*/
	//printf("(4get red: antes da segfault\n");
	return (red);
}
char **get_args(t_token *token)
{
	t_token *tmp;
	int arg_num;
	int i;
	char **args;

	tmp = token;
	arg_num = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD && (!tmp->prev || tmp->prev->type != REDIR))
			arg_num++;
		tmp = tmp->next;
	}
	args = ft_calloc(sizeof(char*) * (arg_num + 1), 1);
	if (!args)
		return (NULL);
	i = 0;
	tmp = token;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD && (!tmp->prev || tmp->prev->type != REDIR))
			(args)[i++] = tmp->str;
		tmp = tmp->next; 
	}
	args[i] = NULL; 
	i = 0 ; 
/*	printf("1get args: antes da segfault\n");     
	while (args[i])
	{
		printf("arg: %d: %s\n", i, args[i]);
		i++;

	}
	printf("2get args: antes da segfault\n");    */	
	return ( args);   
}

t_cmd *get_cmd(t_token *token)
{
    t_cmd *cmd;

    cmd = ft_calloc(sizeof(t_cmd), 1);
    if (cmd == NULL)
    {
        return(NULL);
    }
    cmd->arg = get_args(token);
    if (!cmd->arg)
    {
        return(NULL);
    }
    cmd->red_in = get_red(token, 1);
	cmd->red_out = get_red(token, 0);
//	printf("1ge_cmd: antes da segfault\n"); 
/*	int i = 0 ;    
	while (cmd->arg[i])
	{
		printf("arg: %d: %s\n", i, cmd->arg[i]);
		i++;

	}
//	printf("2get cmd: antes da segfault\n");  
	i = 0 ;   
	while (cmd->red_in[i])
	{
		printf("redir_in %d: %s\n", i, cmd->red_in[i]->str);
		i++;

	}
		i = 0 ;   
	while (cmd->red_out[i])
	{
		printf("redir_out %d: %s\n", i, cmd->red_out[i]->str);
		i++;
	}
	printf("3get cmd:: antes da segfault\n");
	cat explain << a << b < c > 1 >> 2 | ls < Doc1 << Desktop |  echo 123*/
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
 //   printf("cmd_num : %d\n", cmd_num); 
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
