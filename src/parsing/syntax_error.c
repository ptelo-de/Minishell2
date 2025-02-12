#include "parsing.h"

int syntax_check(void)
{
    t_shell *shell;
    t_token *aux;
    
    shell = get_shell();
    if (!shell)
        return (1);
    if (!shell->tokens)
        return (1);
    aux = shell->tokens;
    while(aux)
    {
        if ((aux->type == PIPE && (!aux->prev || aux->prev->type != WORD \
            || !aux->next || aux->next->type == PIPE)) || (aux->type == REDIR \
             && (!aux->next || aux->next->type != WORD))) //maybe is redundant
        {
            ft_putendl_fd("syntax error", 2);
            return (1);
        }
        aux = aux->next;
    }
    return(0);
}
/* 

[] if first token s a pipe then syntax error
[] cuidado com o ||
[] depois redir n posso ter um pipe
[] depois redir posso ter redir
[] depois de um pipe posso redir
[] posso nao ter nada antes da redir e é ok

 */