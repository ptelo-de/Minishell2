
#include "minishell.h"
#include "parsing.h"
#include "builtins.h"
#include "executer.h"

/* MAIN FOR TESTING AST_BUILDING*/
/*int main(int argc, char *argv[], char *envp[])
{
    t_shell *shell;

    (void)argv;
    shell = get_shell();
    check_main_args(argc);
    //if (!envp || !envp[0])
    //    shell->env = env_minus_i();
    //else
        shell->env = get_env(envp);
    shell->exp = get_export(envp);
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
			//printf("\nLEXER\n\n");
			//print_tokens();
			expander();
			//printf("\nEXPANSION\n\n");
			//print_tokens();
			(void)init_cmd();
			//printf("\nCOMANDS ARRAY\n\n");
			//print_cmd_array();
            //printf("\n\n");
            executer();
        }
        free_atributes();
        free(shell->readline);
        shell->readline = NULL;
    }
    //free_arr(shell->env);
    free_arr(shell->exp);
}*/
// cat explain << a << b < c > 1 >> 2 | ls < Doc1 << Desktop |  echo 123
// // *mind the difference between char *argv[] (convention) and char **argv
// int main(int argc, char *argv[], char *envp[])
// {
//     t_shell *shell;

//     (void)argv;
//     shell = get_shell();
//     check_main_args(argc, envp);
//     while(1)
//     {
//         shell->readline = readline("minishell>");
//         add_history(shell->readline); //need to check criteria to add_history
//         //lexer
//         //executer(env)
//         free(shell->readline); //dou free a estrutura toda ? no final do loop? acho que nao
//         shell->readline = NULL;
//     }

// }

/*                            MAIN
t_shell shell;
[] memset(shell, 0, sizeof(t_shell)); is needed? maybe not cause of static object
[] Check main_args
    [] if ac != 1 exit(0)
    [] if !env   // * mind ./minishell env -i //TODO that removes envp
        [] shell.env = env_i_handle();
    [] else
         [] shell.env  env_make();
[] signal handler //pesquisar ara por no loop de execucao
while (1)
[] display
    [] shell->readline= readline("minishell>"); ? tenho de dar free, nao mas tenho de criar um suppfile
    [] add_history(shell->readline);
[] lexer
    
    
    




*/
     
        