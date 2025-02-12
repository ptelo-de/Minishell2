
#include "minishell.h"
#include "parsing.h"
#include "builtins.h"
#include "executer.h"

/* MAIN FOR TESTING AST_BUILDING*/
int main(int argc, char *argv[], char *envp[])
{
    t_shell *shell;
    int     i;
    (void)argv;

    shell = get_shell();
    check_main_args(argc);
    shell->env = get_env(envp);
    shell->exp = get_exp(envp);
    while(1)
    {
        shell->readline = readline("minishell>"); //aprender a defender leaks so readline
//      []  if(!shell->readline)//ctrl D
//      []    	m_exit(shell, NULL); // need exit status //must free env and export
        add_history(shell->readline); //not put white spaces or repetitions
        if (lexer() == 1 || syntax_check() == 1)// need t differ memory error from user input error
        {
            free_atributes();
            //deviamos por exit aqui?
        }
        else
        {
            i = 0;
			printf("\nLEXER\n\n");
			print_tokens();			
            expander();
			printf("\nEXPANSION\n\n");
			print_tokens();
			(void)init_cmd();
			printf("\nCOMANDS ARRAY\n\n");
			print_cmd_array();
            while (shell->cmd[i])
            {
                build_ins(shell->cmd[i]);
                //if (!build_ins(shell->cmd[i]))
                //{
                    //if (!executer(shell->cmd[i]))
                    //    break;
                //}
                i++;
            }
        }
        free_atributes();
        free(shell->readline);
        shell->readline = NULL;
    }
    //free_lst(shell->env);
    //free_lst(shell->exp);
}
// cat explain << a << b < c > 1 >> 2 | ls < Doc1 << Desktop |  "ech"'o' 123



     
        