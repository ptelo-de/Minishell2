
#include "minishell.h"
#include "parsing.h"
#include "builtins.h"

/* MAIN FOR TESTING AST_BUILDING*/
int main(int argc, char *argv[], char *envp[])
{
    t_shell *shell;

    (void)argv;
    shell = get_shell();
    check_main_args(argc);
    //if (!envp || !envp[0])
    //    shell->env = env_minus_i();
    //else
    //    shell->env = array_dup(envp);
    //shell->export_list = array_dup(shell->env); //este export ta mal
	(void)envp;

    while(1)
    {
        shell->readline = readline("minishell>"); //aprender a defender leaks so readline
        if(!shell->readline)//ctrl D
            m_exit(shell, NULL); // need exit status
        add_history(shell->readline); //not put white spaces or repetitions
        if (lexer() == 1 || syntax_check() == 1)// need t differ memory error from user input error
        {
            free_atributes();
        }
        else
        {

			printf("\nLEXER\n\n");
			print_tokens();			expander();
			printf("\nEXPANSION\n\n");
			print_tokens();
			//(void)init_cmd();
			//printf("\nCOMANDS ARRAY\n\n");
			//print_cmd_array();
        }
        free_atributes();
        free(shell->readline);
        shell->readline = NULL;
    }
}
// cat explain << a << b < c > 1 >> 2 | ls < Doc1 << Desktop |  echo 123



     
        