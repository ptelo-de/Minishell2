
#include "parsing.h"

/* //sugetao sergio

t_ast *new_node(int type)
{
	t_ast *aux;

	aux = (t_ast *)malloc(sizeof(t_ast));
	if (!aux)
		aux;

	aux->left = NULL;
	aux->right = NULL;
	aux->fd_in = 0;
	aux->fd_out = 1;
	aux->type = type;
	aux->content = NULL;

}
void clear_lst(t_token *lst)
{
    while(lst)
    {
        free(lst);
        lst = lst->next;
    }
    lst = NULL;
}
t_ast *get_args(t_token *token)
{
    //do
}
void builder_ast(t_ast **ast, t_token *tmp_begin)
{
	t_token *tmp;
	
	tmp = tmp_begin;

	while(tmp != NULL && tmp->type != PIPE)
		tmp = tmp->next;

	if (tmp)
	{
		*ast = new_node(PIPE);
		if(!*ast)
			return;
		builder_ast((*ast)->right, tmp->next);
		clear_lst(tmp);
		tmp->next = NULL;
		builder_ast((*ast)->left ,tmp_begin);
		clear_lst(tmp_begin);
		//trabalho do xuxu e nao nesta funçao, my bad
		// fd_cenas = pipe();
		// t_ast->left->fd_in = fd_cenas[1];
		// t_ast->right->fd_out = fd_cenas[0];
	}
	else 
	{
		*ast = new_node(COMMAND);
		*ast->left = get_args(tmp_begin);
		*ast->right = get_redir(tmp_begin);
		//estes dois podem ser uma unica funçao se preferirem
	}
}
 */