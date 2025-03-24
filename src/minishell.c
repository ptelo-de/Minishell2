
#include "minishell.h"
#include "parsing.h"
#include "executer.h"

/* MAIN FOR TESTING AST_BUILDING*/
int main(int argc, char *argv[], char *envp[])
{
    t_shell *shell;
    //int     i;
    (void)argv;

    shell = get_shell();
    check_main_args(argc);
    shell->env = get_env(envp);
    shell->exp = get_exp(envp);
    while(1)
    {
        interactive_mode();
        shell->readline = readline("minishell>"); //aprender a defender leaks so readline
        ignore_signal(SIGINT);
        if(!shell->readline)//ctrl D
        {
            free_atributes();
            printf("exit\n");
            free_lst(shell->env);
            free_lst(shell->exp);
            exit(0);
          //  ms_exit(shell, shell->cmd); // need exit status //must free env and export
        }
//      
		//fim do modo interativo: SIG_Ignore CRTL_C  E SIG_iGNORE CTRL_/
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
			printf("\nEXPANSION\n\n");
			print_tokens();
			(void)init_cmd();
			printf("\nCOMANDS ARRAY\n\n");
			print_cmd_array();
            shell->exit_status = 0; //importante, isto ja foi usado no expander e agora é preciso impar o ex code do cmd anterior
            executer();
        }
        free_atributes();
        free(shell->readline);
        shell->readline = NULL;
    }
    free_lst(shell->env);
    free_lst(shell->exp);
}



     
        