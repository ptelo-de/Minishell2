
/*#include "builtins.h"

int m_pwd(t_shell *shell, char **args)
{
    char *tmp;

    (void)shell;
    (void)args;
    tmp = getcwd(NULL, 0); // Dynamically allocate the current working directory
    if (!tmp)
        return (EXIT_FAILURE);
    ft_putendl_fd(tmp, 1); // Print the current working directory
    free(tmp);
    return (EXIT_SUCCESS);
}*/
