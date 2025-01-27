
#include "parsing.h"

char *get_value(char *name)
{
    t_shell *shell;
    t_list *tmp;
    size_t name_len;

	shell = get_shell();
    if (!name || !(shell))
    {
        return NULL;
    }
    tmp = shell->env;
    name_len = ft_strlen(name);

    while (tmp)
	{
        if (ft_strncmp(tmp->content, name, name_len) == 0 && ((char *)tmp->content)[name_len] == '=')
		{
            return ((char*)tmp->content + name_len + 1);
        }
        tmp = tmp->next;
    }
    return NULL;
}

void	process_dollar(int *len, char *src, char **update)
{
	int i;
	char *aux;
	char *auxx;

	if (!ft_isalpha(src[1]) && src[1] != '_')
	{
		aux = *update;
		*update= ft_strjoin(aux, "$");
		if (aux)
			free(aux);
		(*len)++;
		return;
	}
	else
	{
		i = 1;
		while (ft_isalnum(src[i]) || src[i] == '_')
			i++;
		auxx = ft_substr(src, 1, i);
		aux = *update;
		*update = ft_strjoin(aux, get_value(auxx));
		if (aux)
			free(aux);
		if (auxx)
			free(auxx);
		*len = *len + i + 1;
	}
}
void expand_quote(int *i, char **update, char *src)
{
	char quote;
	int len;
	char *aux;
	char *auxx;

	quote = *src;
	len = 0;
	while (src[len])
	{
		if (quote == '\'' && len > 0 && src[len] == '\'')
		{
			auxx = ft_substr(src, *i + 1, len - 1);
			aux = *update;
			*update = ft_strjoin(aux, auxx);
			if (aux)
				free(aux);
			if (auxx)
				free(auxx);
			break;
		}
		if (quote == '\"' &&  len > 0 && (src[len] == '\"' || src[len] == '$'))
		{
			if (quote == '\"' && src[len] == '$')
				process_dollar( &len ,src + len, update);
			else
			{
				auxx = ft_substr(src, *i + 1, len);
				aux = *update;
				*update = ft_strjoin(aux, auxx);
				if (aux)
					free(aux);
				if (auxx)
					free(auxx);
				break;
			}
		}
		len++;
	}
	*i += len;
}


void expander(void) // falta fazer funçao para limpar nodes com strings vazias, que foram expandidas para null
{
	t_token *tmp;
	t_shell *shell;
	int i;
	char *update;
	char *aux;

	shell = get_shell();
	if (!shell || !shell->tokens)
		return;
	tmp = shell->tokens;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			i = 0;
			while (tmp->str[i])
			{
				if (tmp->str[i] == '\'' || tmp->str[i] == '\"')
				{
					expand_quote(&i, &update, tmp->str + i);
				}
				else if (tmp->str[i] == '$')
					process_dollar(&i, tmp->str + i, &update);
				else
				{
					i++;
					aux = update;
					update = ft_strjoin(aux, &tmp->str[i]);
					if (aux)
						free(aux);
				}
			}
			if (update)
				tmp->str = update;
			else
				tmp->str = NULL;
		}
		tmp = tmp->next;
	}
}



//			/*
//			[] i = 0;
//			[] [] while (s[i])
//				[]	if (s[i] == '\'' || s[i] == '\"')
//					[] Encontro a primeira single quote e, se não tiver dentro de uma double quote, tiro a '
//					[] Salto até à segunda single quote e, se não tiver dentro de uma double quote, tiro a '
//					[] Encontrei a primeira double quote e, se não tiver dentro de uma single quote quote, tiro a "
//						[] se encontrar um $, guarda o name a seguir até char fora das regras e expande
//					[] Salto até à segunda double quote e, se não tiver dentro de uma single quote, tiro a "
//			[] else
//				[] if (s[i] == '=')
//					[] pegar o que estava antes ate idenaçao ou aspa
//					[] guardar num buffer, tudo desde o inicio passando pelo = e ate um espço ou aspa
//					[] ft_list_add_back
//					[) andar essas casas todas na string original
//				[] else if (s[i] == '$')
//					[] char *name_var
//					[] name_var = guarda o name a seguir até char fora das regra
//					[] if (!name)
//						não tira dollar sign
//					[] else
//						[] expand name, includes removing name and dollar attatched
//			 */



//			/*
//			[] i = 0;
//			[] [] while (s[i])
//				[]	if (s[i] == '\'' || s[i] == '\"')
//					[] Encontro a primeira single quote e, se não tiver dentro de uma double quote, tiro a '
//					[] Salto até à segunda single quote e, se não tiver dentro de uma double quote, tiro a '
//					[] Encontrei a primeira double quote e, se não tiver dentro de uma single quote quote, tiro a "
//						[] se encontrar um $, guarda o name a seguir até char fora das regras e expande
//					[] Salto até à segunda double quote e, se não tiver dentro de uma single quote, tiro a "
//			[] else
//				[] if (s[i] == '=')
//					[] pegar o que estava antes ate idenaçao ou aspa
//					[] guardar num buffer, tudo desde o inicio passando pelo = e ate um espço ou aspa
//					[] ft_list_add_back
//					[) andar essas casas todas na string original
//				[] else if (s[i] == '$')
//					[] char *name_var
//					[] name_var = guarda o name a seguir até char fora das regra
//					[] if (!name)
//						não tira dollar sign
//					[] else
//						[] expand name, includes removing name and dollar attatched
//			 */


///*
//Regras nomes de variaveis: 
//[] primeiro char do nome a seguir ao dollar so pode ser um _ ou uma letra alphabetica
//[] o resto do nome pode ser _ letras alphabeticas ou digitos

//c1r8s12% bash
//ptelo-de@c1r8s12:~/Documents/minishell$ echo $.ola
//$.ola
//ptelo-de@c1r8s12:~/Documents/minishell$ echo $ola

//ptelo-de@c1r8s12:~/Documents/minishell$ echo $%ola
//$%ola
//ptelo-de@c1r8s12:~/Documents/minishell$ echo $5ola
//ola
//ptelo-de@c1r8s12:~/Documents/minishell$ 

//nem $$ nem o ~ nem o $5, mas por exemplo $0 tem de expandir 
//---------------------------------------------------------------------------------------------------------------------------

//pilar@pilar-ThinkPad:~/Documents/minishell$ echo "$USER"
//pilar
//pilar@pilar-ThinkPad:~/Documents/minishell$ echo '"$USER"'
//"$USER"
//pilar@pilar-ThinkPad:~/Documents/minishell$ echo "'$USER'"
//'pilar'
//pilar@pilar-ThinkPad:~/Documents/minishell$ echo '$USER'
//$USER
//pilar@pilar-ThinkPad:~/Documents/minishell$ 
//--------------------------------------------------------------------------------------------------------------------------------
//ptelo-de@c1r1s12:~/Documents/minishell$ $suppor
//ptelo-de@c1r1s12:~/Documents/minishell$ $support
//HELLO: command not found
//ptelo-de@c1r1s12:~/Documents/minishell$ echo "$support"
//HELLO          WORLD
// */