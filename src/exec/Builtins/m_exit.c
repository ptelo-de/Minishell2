
#include "builtins.h"
#include <limits.h>

int m_exit(t_shell *shell, char **args)
{
    int i = 0;
    int exit_code = 0;
    
    //(void)shell;
    ft_putstr_fd("exit\n", 1);
    if (shell->readline)
        free(shell->readline);
    if (shell->env)
        free_array(shell->env);
    if (shell->export_list)
        free_array(shell->export_list);
    if (!args)
        exit(0);
    if(!args[1])
    {
        free_array(args);
        exit(0);
    }
    if (args[1][0] == '+' || args[1][0] == '-')
        i++;
    while (args[1][i])
    {
        if(!ft_isdigit(args[1][i]))
        {
            ft_putstr_fd("minishell: exit: ", 2);
            ft_putstr_fd(args[1], 2);
            ft_putstr_fd(": numeric argument required\n", 2);
            free_array(args);
            exit(255);//Exit with 255 for invalid numeric argument
        }
        i++;
    }
    if (args[2])
    {
        ft_putstr_fd("minishell: exit: too many arguments\n", 2);
        return (1);
    }
    exit_code = ft_atoi(args[1]);
    free_array(args);
    exit((unsigned char)exit_code);
    return (0);
}
