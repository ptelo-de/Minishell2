#include "parsing.h"

void    free_tokens(void)
{
    t_shell *shell = get_shell();
	t_token *next;

    while (shell->tokens)
    {
       	next = shell->tokens->next;
        if (shell->tokens->str)
        {
            free(shell->tokens->str);
            shell->tokens->str = NULL;
        }
        free(shell->tokens);
		shell->tokens = NULL;
        shell->tokens = next;
    }
    shell->tokens = NULL;
}

void free_atributes(void)
{
	free_tokens();
	free_cmds();
}
