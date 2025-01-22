#include "parsing.h"

void add_token(int start, int len, t_type type)
{
    t_shell *shell = get_shell();
    t_token *token;

    token = ft_calloc(1, sizeof(t_token));
    if (!token)
    {
        ft_putendl_fd("error allocating token", 2);
        free_atributes();
        exit(1); // which xit code is best?
    }
    // printf("new token: %p \n", token);
    token->type = type;
    token->str = ft_substr(shell->readline, start, len);
    token->next = NULL;
    token->prev = tokenlast(shell->tokens);
    if (token->prev)
        token->prev->next = token;
    else
      shell->tokens = token;
}

t_token	*tokenlast(t_token *first)
{
	t_token *token;

    token = first;
    if (!token)
		return (NULL);
	while (token->next)
		token = token->next;
	return (token);
}


void    free_tokens(void)
{
    t_shell *shell = get_shell();
    t_token *aux = shell->tokens;

    while (aux)
    {
        t_token *next = aux->next;
        if (aux->str)
        {
            free(aux->str);
            aux->str = NULL;
        }
        free(aux);
        aux = next;
    }
    shell->tokens = NULL;
}

void free_atributes(void)
{
	t_shell *shell;
	int k;
	int i;

	free_tokens();
	shell = get_shell();
	k = 0;
	while (shell && shell->cmd && shell->cmd[k])
	{
		if (shell->cmd[k]->arg)
			free (shell->cmd[k]->arg);
		shell->cmd[k]->arg = NULL;
		i = 0;
		while (shell->cmd[k]->red_in && shell->cmd[k]->red_in[i])
		{
			shell->cmd[k]->red_in[i]->str = NULL;
			free (shell->cmd[k]->red_in[i]);
			shell->cmd[k]->red_in[i++] = NULL;
		}
		if (shell->cmd[k]->red_in)
			free (shell->cmd[k]->red_in);
		shell->cmd[k]->red_in = NULL;
		i = 0;
		while (shell->cmd[k]->red_out && shell->cmd[k]->red_out[i])
		{
			shell->cmd[k]->red_out[i]->str = NULL;
			free (shell->cmd[k]->red_out[i]);
			shell->cmd[k]->red_out[i++] = NULL;
		}
		if (shell->cmd[k]->red_out)
			free (shell->cmd[k]->red_out);
		shell->cmd[k]->red_out = NULL;
		free(shell->cmd[k]);
		shell->cmd[k++] = NULL;

	}
	if (shell && shell->cmd)
		free (shell->cmd);
	shell->cmd = NULL;
}

