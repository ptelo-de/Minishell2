
/*#include "builtins.h"
int	ft_strcmp(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] && str1[i] == str2[i])
		i++;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
int (*btin_arr(char *command))(t_shell *shell, char **args)
{ //comd é o meu array zero que vou comparar
  // isto é o que para as funções
    static void	*builtin[7][2] = {
    {"cd", m_cd}, // se cd for o commando eu vou para a função de tal
    {"echo", m_echo},
    {"pwd", m_pwd},
    {"export", m_export},
    {"unset", m_unset},
    {"env", m_env},
    {"exit", m_exit},
    };
    int     i;
    
    i = 0;
    while (i < 7)
    {
        if (command)
        {
            if (!ft_strcmp(builtin[i][0], command))
                return (builtin[i][1]);
            i++;
        }
    }
    return (NULL);
}
*/