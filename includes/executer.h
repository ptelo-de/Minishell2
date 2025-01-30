#ifndef EXECUTER_H
# define EXECUTER_H

# include "minishell.h"
# include "builtins.h"

void	free_arr(char **arr);

//char	**get_env(char **envp);
t_list	*get_env(char **envp);
char	**get_export(char **envp);

void	executer();

#endif