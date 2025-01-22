
#include "parsing.h"


int has_dollar(const char *str) {
    if (!str) {
        return 0;
    }
    while (*str) {
        if (*str == '$') {
            return 1;
        }
        str++;
    }
    return 0;
}

void remove_single_quote(t_token **tmp)
{
	char *new_str;
	int i;
	int end;
	int j;

	if (!((*tmp)->str))
		return;
	end = ft_strlen((*tmp)->str) - 2;
	new_str = ft_calloc(1, sizeof(char)* (end + 1));
	if (!new_str)
	{
	    free_tokens();
		return;
	}
	i = 1;
	j = 0;
	while (i <= end)
	{
		new_str[j++] = (*tmp)->str[i++];
	}
	free((*tmp)->str);
	(*tmp)->str = new_str;
}
void remove_double_quotes(t_token **tmp) {
    
	char *new_str;
	int i;
	int j;

    if (!(*tmp)->str || !(*tmp)->str[0])
        return;
    new_str = ft_calloc(1, sizeof(char) * (strlen((*tmp)->str) + 1));
    if (!new_str)
    {
        return;
    }
	i = 0;
	j = 0;
    while ((*tmp)->str[i]) {
        if ((*tmp)->str[i] != '"') {
            new_str[j] = (*tmp)->str[i];
			j++;
        }
        i++;
    }
    free((*tmp)->str);
    (*tmp)->str = new_str;
}
void expander(void)
{
    t_token *tmp;
    t_shell *shell;
    int i;

    shell = get_shell();
    if (!shell || !shell->tokens) {
        return;
    }
    tmp = shell->tokens;
    while (tmp) {
        if (tmp->type == WORD) {
            i = 0;
            if (tmp->str[0] != '\'') {
                while (tmp->str[i] && has_dollar(tmp->str + i)) {
                    handle_one_dollar(&i, &tmp);
                }
				remove_double_quotes(&tmp);
            }
			else
				remove_single_quote(&tmp);
        }
        tmp = tmp->next;
    }
}

/*
Regras nomes de variaveis: 
[] primeiro char do nome a seguir ao dollar so pode ser um _ ou uma letra alphabetica
[] o resto do nome pode ser _ letras alphabeticas ou digitos

c1r8s12% bash
ptelo-de@c1r8s12:~/Documents/minishell$ echo $.ola
$.ola
ptelo-de@c1r8s12:~/Documents/minishell$ echo $ola

ptelo-de@c1r8s12:~/Documents/minishell$ echo $%ola
$%ola
ptelo-de@c1r8s12:~/Documents/minishell$ echo $5ola
ola
ptelo-de@c1r8s12:~/Documents/minishell$ 

nem $$ nem o ~ nem o $5, mas por exemplo $0 tem de expandir 
---------------------------------------------------------------------------------------------------------------------------

pilar@pilar-ThinkPad:~/Documents/minishell$ echo "$USER"
pilar
pilar@pilar-ThinkPad:~/Documents/minishell$ echo '"$USER"'
"$USER"
pilar@pilar-ThinkPad:~/Documents/minishell$ echo "'$USER'"
'pilar'
pilar@pilar-ThinkPad:~/Documents/minishell$ echo '$USER'
$USER
pilar@pilar-ThinkPad:~/Documents/minishell$ 
--------------------------------------------------------------------------------------------------------------------------------
ptelo-de@c1r1s12:~/Documents/minishell$ $suppor
ptelo-de@c1r1s12:~/Documents/minishell$ $support
HELLO: command not found
ptelo-de@c1r1s12:~/Documents/minishell$ echo "$support"
HELLO          WORLD
 */