#include "parsing.h"

/* 
[] int redir(void)
{
[]    t_shell *shell;
[]    t_token *token;

[]    shell = get_shell();
[]    if (!shell)
[]        return (1);
[]    token = shell->tokens;
[]    while(token)
    {
        if (token->type == REDIR && !ft_strncmp(token->str, "<<", 2))
    }
}
------------------------------------------------------------------------------------------------------------------
gomes@DESKTOP-TB8EKU6:~/minishell$ bash
gomes@DESKTOP-TB8EKU6:~/minishell$ echo > 123
gomes@DESKTOP-TB8EKU6:~/minishell$ chmod 000 123
gomes@DESKTOP-TB8EKU6:~/minishell$ cat << a < 123 | cat << b
a
b
bash: 123: Permission denied
gomes@DESKTOP-TB8EKU6:~/minishell$ cat << a < 123 | cat << b
ola
a
adeus
b
bash: 123: Permission denied
adeus
gomes@DESKTOP-TB8EKU6:~/minishell$ 
--------------------------------------------------------------------------------------------------------------------
*/

//ambiguos redirecton mind, ex redirecting to multiplr files
//in side buil a tree do heredoc, heredoc 


/*
 << 'eof' cat
> 
bash: warning: here-document at line 44 delimited by end-of-file (wanted `eof')

great test for redirections: cat < a << eof < b > o1 >> o2 > o3 | ls
aqui here docs are done, and opening the files is tested, if not a not exists it stops here,
if out put filles dont exists they are  created.
cat vai so buscar o b mas o here doc é feito na mesma
! CUIDADO COM LEAKS

(nota :termius)
o que difere do get next line e o readline e que ao readline lida com os sinais de forma adecuada para o heredoc
*/
