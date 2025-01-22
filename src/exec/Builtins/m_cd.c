
#include "builtins.h"

int update_env_var(t_shell *shell, const char *key, const char *value)
{
    char *new_var;
    int len;

    len = ft_strlen(key) + ft_strlen(value) + 2; // Key + '=' + Value + '\0'
    new_var = malloc(len);
    if (!new_var)
        return (1);
    ft_strlcpy(new_var, key, len);
    ft_strlcat(new_var, "=", len);
    ft_strlcat(new_var, value, len);
    shell->env = add_or_update_var(shell->env, new_var);
    shell->export_list = add_or_update_var(shell->export_list, new_var);
    free(new_var);
    return (0);
}


int m_cd(t_shell *shell, char **args)
{
    char *target_dir;
    char cwd[PATH_MAX];//to store the current working directory
    char *oldpwd;

    if (!args[1] || !ft_strcmp(args[1], "~"))// no argument or '~': go to HOME
    {
        target_dir = getenv("HOME"); //get HOME from the environment
        if (!target_dir)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", 2);
            return (1);
        }
    }
    else if (!ft_strcmp(args[1], "-"))//'-' argument: go to OLDPWD
    {
        target_dir = getenv("OLDPWD");
        if (!target_dir)
        {
            ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
            return (1);
        }
        ft_putstr_fd(target_dir, 1);//print the OLDPWD directory
        ft_putstr_fd("\n", 1);
    }
    else
        target_dir = args[1];//use provided directory
    if (getcwd(cwd, sizeof(cwd)) == NULL)//get the current directory before changing it
        ft_putstr_fd("minishell: cd: error retrieving current directory\n", 2);
    if (chdir(target_dir) != 0)//change to the target directory
    {
        ft_putstr_fd("minishell: cd: ", 2);
        ft_putstr_fd(args[1], 2);
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(strerror(errno), 2);//print the system error message
        ft_putstr_fd("\n", 2);
        return (1);
    }
    oldpwd = ft_strdup(cwd); // Save the old PWD
    if (getcwd(cwd, sizeof(cwd)) != NULL) // Update PWD
        update_env_var(shell, "PWD", cwd);
    update_env_var(shell, "OLDPWD", oldpwd);
    free(oldpwd);
    return (0);
}
