/*#include "builtins.h"

 int main(int argc, char *argv[], char *envp[])
{
    t_shell *shell;
    char **test;//Parsed input
    int (*builtin_func)(t_shell *, char **);//Function pointer for the built-in

    (void)argv;
    check_main_args(argc, envp);
    shell = get_shell();
    if (!envp || !envp[0])//Check if envp is empty (env -i case)
        shell->env = env_minus_i();
    else
        shell->env = array_dup(envp);//Duplicate envp and store it in shell->env
    shell->export_list = array_dup(shell->env);//Initialize export_list as a copy of env
    while (1)
    {
        shell->readline = readline("minishell> ");
        if (!shell->readline)//Exit on Ctrl+D
            m_exit(shell, NULL);
        add_history(shell->readline);
        test = ft_split(shell->readline, ' ');//Split input into arguments
        if (!test || !test[0])//Handle empty input
        {
            free_array(test);
            continue;
        }
        builtin_func = btin_arr(test[0]);
        if (builtin_func)
            builtin_func(shell, test);//Call the built-in function dynamically
        else
            printf("Command not found: %s\n", test[0]);
        free(shell->readline);
        shell->readline = NULL;
        free_array(test);
    }
} */
