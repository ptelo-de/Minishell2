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
        exit(1);
    }
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
