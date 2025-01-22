
#include "builtins.h"

char **array_dup(char *env[])
{
    int i;
    char **new_env;

    i = 0;
    if (!env) // hande NULL input
        return NULL;
    while (env[i]) //count the number of str in the env
        i++;
    new_env = malloc(sizeof(char *) * (i + 1));
    if (!new_env)
        return NULL;
    i = 0;
    while (env[i])
    {
        new_env[i] = ft_strdup(env[i]);
        if (!new_env[i]) // handle memory allocation failure
        {
            while (--i >= 0)
                free(new_env[i]);
            free(new_env);
            return NULL;
        }
        i++;
    }
    new_env[i] = NULL;
    return (new_env);
}

char **env_minus_i(void)
{
    char *pwd;
    char **new_env_i;
    int i;
    
    i = 0;
    new_env_i = malloc(sizeof(char *) * 4); // default env with 3 variables + NULL
    if (!new_env_i)
        return NULL;
    pwd = getcwd(NULL, 0);
    if (!pwd)
    {
        free(new_env_i);
        return NULL;
    }
    new_env_i[i++] = ft_strjoin("PWD=", pwd);
    free(pwd);
    new_env_i[i++] = ft_strdup("SHLVL=1");
    new_env_i[i++] = ft_strdup("_=/usr/bin/env");
    new_env_i[i] = NULL;
    return new_env_i;
}

int m_env(t_shell *shell, char **args) //env está dentro do minishell e aceder ao env dentro da estrutura 
{
    int i;

    (void)args;
    i = 0;
    if (!shell->env || !shell->env[0])
        return (EXIT_SUCCESS);
    while (shell->env[i]) // Print the environment variables
    {
        ft_putstr_fd(shell->env[i], 1);
        ft_putstr_fd("\n", 1);
        i++;
    }
    return (EXIT_SUCCESS);
}


// CRIAR O NOSSO PROPRIO FREE
    //FREE recebe *s
/*     if pointer
            free(pointer);
            pointer = '\0'
        return ;
*/

//PARA FECHAR FILE DESCRIPTORS
    /* while(i <= file descriptor max) 
        close(i) //pq nao faz mal fechar file descriptores que não estão abertos
     */