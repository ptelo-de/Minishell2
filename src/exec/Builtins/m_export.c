
#include "builtins.h"

void print_export_list(char **export_list)
{
    int i = 0;
    char *equals_sign;
    char *key;
    char *value;
    int key_length;

    bubble_sort(export_list);
    while (export_list && export_list[i])
    {
        equals_sign = ft_strchr(export_list[i], '=');
        if (equals_sign)
        {
            key_length = equals_sign - export_list[i];  // Length of key
            key = ft_substr(export_list[i], 0, key_length);  // Extract key
            value = equals_sign + 1;  // The part after '=' is the value
            ft_putstr_fd("declare -x ", 1);
            ft_putstr_fd(key, 1);
            ft_putstr_fd("=\"", 1);  // Print the opening quote
            ft_putstr_fd(value, 1);   // Print the value
            ft_putstr_fd("\"\n", 1);  // Print the closing quote
            free(key);
        }
        else
        {
            // No value, just print the variable
            ft_putstr_fd("declare -x ", 1);
            ft_putstr_fd(export_list[i], 1);
            ft_putstr_fd("\n", 1);
        }
        i++;
    }
}

int get_var_pos(char **list, const char *var) 
{
    int i;
    size_t var_len;
    size_t name_len;
    char *var_name;
    char *name;

    i = 0;
    var_len = ft_strchr(var, '=') - var;//calculate the length of the name part of `var` (up to the `=` character)
    name = strndup(var, var_len);//extract the name part from var
    while (list && list[i]) 
    {
        name_len = ft_strchr(list[i], '=') - list[i];//calculate the length of the name part of the current list variable
        var_name = strndup(list[i], name_len);//extract the name part from the current list variable
        if (ft_strcmp(var_name, name) == 0)//compare the names. If they match, return the index
        {
            free(var_name);
            free(name);
            return (i);
        }
        free(var_name);
        i++;
    }
    free(name);
    return (-1);
}

char **add_or_update_var(char **list, const char *var)
{
    int position;
    char **new_list;
    int i;
    char *equal_sign_pos;

    position = get_var_pos(list, var);
    if (position != -1) // If variable exists, update it
    {
        equal_sign_pos = ft_strchr(var, '=');
        if (equal_sign_pos != NULL)
        {
            free(list[position]); // Free the old variable string
            list[position] = ft_strdup(var); // Assign the new variable string
        }
        return list;
    }
    i = 0;
    while (list && list[i])//count the current variables
        i++;
    new_list = malloc(sizeof(char *) * (i + 2));//allocate space for one more variable + NULL terminator
    if (!new_list)
        return NULL;
    i = 0;
    while (list && list[i])//copy existing variables into the new list
    {
        new_list[i] = list[i];
        i++;
    }
    new_list[i] = ft_strdup(var);//add the new variable (name=value)
    new_list[i + 1] = NULL; //null-terminate the new list
    free(list); //free the old list
    return new_list;
}

int m_export(t_shell *shell, char **args)
{
    int i;
    i = 1;

    if (!args[1]) //no argumentss / print export list
    {
        print_export_list(shell->export_list);
        return (EXIT_SUCCESS);
    }
    while (args[i])
    {
        if (ft_strchr(args[i], '='))
            shell->env = add_or_update_var(shell->env, args[i]); //update env
        shell->export_list = add_or_update_var(shell->export_list, args[i]); //update export_list
        i++;
    }
    return (EXIT_SUCCESS);
}
