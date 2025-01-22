#include "minishell.h"
#include "parsing.h"
#include "builtins.h"

void print_tokens(void)
{
    t_shell *shell = get_shell();
    t_token *token;
    token = shell->tokens;
    if (!token)
        return;
    printf("TOKENS NEXT: ");
    while(token)
    {
        printf("%p -> ",token);
        token = token->next; 
    }
    printf("\n");
    token = tokenlast(shell->tokens);
    printf("TOKENS PREV: ");
    while(token)
    {
        printf("<- %p" ,token);
        token = token->prev; 
    }
    token = shell->tokens;
    printf("\n");
    printf("STR : ");
    while(token)
    {
        printf("%s ",token->str);
        token = token->next; 
    }
        token = shell->tokens;
    printf("\n");
    printf("TYPE : ");
    while(token)
    {
        printf("%u ",token->type);
        token = token->next; 
    }
    printf("\n");
}
void print_cmd_array(void)
{
	t_shell	*shell;
	int	k;
	int	i;

	shell = get_shell();
	k = 0;
	while (shell->cmd[k])
	{
	printf("Command %d\n", k);
	i = 0;
	while (shell->cmd[k]->arg[i])
	{
		printf("arg %d: %s\n", i, shell->cmd[k]->arg[i]);
		i++;
	}
	i = 0;
	while (shell->cmd[k]->red_in && shell->cmd[k]->red_in[i])
	{
		printf("red_in %d: %s\n", shell->cmd[k]->red_in[i]->type, shell->cmd[k]->red_in[i]->str);
		i++;
	}
	i = 0;
	while (shell->cmd[k]->red_out && shell->cmd[k]->red_out[i])
	{
		printf("red_out %d: %s\n", shell->cmd[k]->red_out[i]->type, shell->cmd[k]->red_out[i]->str);
		i++;
	}
	k++;
	}
}