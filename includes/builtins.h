
#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

# define PWD "PWD="
# define OLDPWD "OLDPWD="
# define HOME "HOME="
# define PATH "PATH="

int 		m_echo (t_shell *shell, char **args);
int     	m_pwd(t_shell *shell, char **args);
char		**array_dup(char *env[]);
int			m_env(t_shell *shell, char **args);
char 		**env_minus_i(void);
int 		m_exit(t_shell *shell, char **args);
void 		print_export_list(char **export_list);
int 		get_var_pos(char **list, const char *var);
char 		**add_or_update_var(char **list, const char *var);
int 		m_export(t_shell *shell, char **args);
void		bubble_sort(char **matrix);
void 		free_array(char **array);
char 		**remove_var(char **list, const char *var);
int 		m_unset(t_shell *shell, char **args);
int 		update_env_var(t_shell *shell, const char *key, const char *value);
int 		m_cd(t_shell *shell, char **args);
int 		(*btin_arr(char *command))(t_shell *shell, char **args);
int	ft_strcmp(const char *str1, const char *str2);


#endif