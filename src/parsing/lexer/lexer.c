
// a<<a<a 
#include "parsing.h"

void white_space_skip(int *i)
{
    t_shell *shell;
    char *s;

    shell = get_shell();
    s = shell->readline;
    while (s[*i] && (s[*i] == ' ' || s[*i] == '\t' || s[*i] == '\n'))
        *i = *i + 1;
}
int quote_skip(int *i)
{
    t_shell *shell = get_shell();
    char c;
    int j;
	
	c = shell->readline[*i];
	j = *i;
    (*i)++;
    while ( shell->readline[*i] && shell->readline[*i] != c)
        (*i)++;
    if (shell->readline[*i] == c)
    {
        (*i)++;
		add_token(j, *i - j, WORD);
        return (0);
    }    
    else
        return(1);     
}
void word_skip(int *i)
{
	t_shell *shell;
	int j;

	j = *i;
	shell = get_shell();
	while (shell->readline[*i] \
	&& shell->readline[*i] != '\'' \
	&& shell->readline[*i] != '\"' \
	&& shell->readline[*i] != '|' \
	&& shell->readline[*i] != ' ' \
	&& shell->readline[*i] != '\t' \
	&& shell->readline[*i] != '\n' \
	&& shell->readline[*i] != '<' \
	&& shell->readline[*i] != '>')
		(*i)++;
	add_token(j, *i - j, WORD);
}
void redir_skip(int *i)
{
    t_shell *shell;
    int j;

    j = *i;
    shell = get_shell();
	if (shell->readline[*i + 1] == shell->readline[*i])
	{
		(*i) = *i + 2;
		return(add_token(j, 2, REDIR));
	}
	add_token(j, 1, REDIR);
	(*i)++;
}

int lexer(void)
{
    t_shell *shell;
    int i;

    shell = get_shell();
    i = 0;
    while(shell->readline[i])
    {
		white_space_skip(&i);
		if (shell->readline[i] == '\'' || shell->readline[i] == '\"')
		{
			if (quote_skip(&i) == 1)
			{
				ft_putendl_fd("quotes error", 2);
				return(1);
			}
		}
		else if (shell->readline[i] == '|')
		{
			add_token(i, 1, PIPE);
			i++;
		}        
		else if (shell->readline[i] == '<' || shell->readline[i] == '>' )
			redir_skip(&i);
		else
			word_skip(&i);;
    }
    return (0);
}

/*
criterio para encontrar tokens
[] quando vejo plicas ver se depois tem outra  plica e o mesmo para ""


[] procurar espacos e simbolos pois eles separam tokens, ainda que simbolos tambem sejam tokes, aspas e plicas nã0 separam necessariamente words
a"$USER" = apilar
a'$USER' = a$user
a"'$USER'" = a'pilar' , aqui são duas words ou uma só (porque eu tenho de manter as plicas)?
aspas e plicas não sao tokens mas não são separadores de palavras
.Conceito de token, ver man bash


[]atenção a condição || porque sao dois pipes a frente um do outro


fazer um split com um set de separadores (white spaces, pipe, 4 redir)
fazer um sip_until_char(char c)

[] metacarecters  a considerar: white spaces(fore de aspas), pipe, 4 redir, aspas, plicas, dolar
*/
