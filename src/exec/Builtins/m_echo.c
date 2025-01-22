
#include "builtins.h"

int m_echo (t_shell *shell, char **args)
{
    int newline; 
    int i;

    (void)shell;
    i = 1;
    newline = 1; //default
    while (args[i] && args[i][0] == '-' && args[i][1] == 'n') //Check for the "-n" option
    {
        int j = 2;  // Start checking after "-n"
        while (args[i][j] == 'n') 
        {
            j++;
        }
        if (args[i][j] != '\0') // If there are other characters, break the loop
            break;
        newline = 0;
        i++;
    }
    while(args[i]) //Print arguments
    {
        ft_putstr_fd(args[i], 1);
        if(args[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
    if (newline) //exist
        ft_putstr_fd("\n", 1);
    return(EXIT_SUCCESS);
}
