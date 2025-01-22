
#include "builtins.h"

char **remove_var(char **list, const char *var)
{
    int i = 0, j = 0;
    char **new_list;

    if(get_var_pos(list, var) == -1)
        return (list);
    while (list && list[i])
        i++;
    new_list = malloc(sizeof(char *) * i); // No +1 because we're removing one
    if (!new_list)
        return NULL;
    i = 0;
    while (list && list[i])
    {
        char *key = ft_strdup(list[i]); // Duplicate to manipulate
        char *equal_sign = ft_strchr(key, '='); // Find '=' in the variable
        if (equal_sign)
            *equal_sign = '\0'; // Temporarily terminate at '=' to extract the key
        if (ft_strcmp(key, var) == 0) // Compare the key with the variable to remove
            free(list[i]); // Free the variable being removed
        else
            new_list[j++] = list[i]; // Copy to the new list
        free(key); // Free the temporary key
        i++;
    }
    new_list[j] = NULL; // Null-terminate the new list
    free(list); // Free the old list
    return new_list;
}

int m_unset(t_shell *shell, char **args)
{
    int i = 1;

    if (!args[1])
        return (EXIT_SUCCESS);
    while (args[i])//remove each argument from env and export_list
    {
        shell->env = remove_var(shell->env, args[i]);
        shell->export_list = remove_var(shell->export_list, args[i]);
        i++;
    }
    return (EXIT_SUCCESS);
}

//quando faço export a, ele cria a tal variavel, mas quando uso o unset a obtenho isto
//==33386== Invalid write of size 8
//==33386==    at 0x109E23: remove_var (m_unset.c:28)
//==33386==    by 0x109E9A: m_unset (m_unset.c:41)
//==33386==    by 0x10B2C5: main (main_exec.c:44)
//==33386==  Address 0x4b5b258 is 0 bytes after a block of size 328 alloc'd
//==33386==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
//==33386==    by 0x109D03: remove_var (m_unset.c:11)
//==33386==    by 0x109E9A: m_unset (m_unset.c:41)
//==33386==    by 0x10B2C5: main (main_exec.c:44)
//==33386==