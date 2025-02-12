#ifndef EXECUTER_H
# define EXECUTER_H

# include "minishell.h"
# include "builtins.h"

void	free_arr(char **arr);
t_list	*get_env(char **envp);
char	*put_double_quotes(char *str);
int		is_longer(char	*str1, char	*str2);
int		is_repeated_arr(char *str, char **env_order);
char	*get_smallest(char **env_order, char **envp);
int		arr_len(char **arr);
char	 **alpha_order(char **envp);
t_list	*get_exp(char **envp);
int		flag_n(char *arg);
void	ms_echo(t_cmd *cmd);
void	ms_cd(t_list **env, t_list **exp, t_cmd *cmd);
void	ms_pwd();
int		has_equal(char *var);
void	put_export_mid_end(t_list **exp, char *var, t_list *new_node);
void	put_export(t_list **exp, char *var);
char	*trim_value(char *var);
int		update_lst(t_list **lst, char *var, int b);
void	ms_export(t_list **env, t_list **exp, t_cmd *cmd);
void	delete_var(t_list **lst, char *var);
void	ms_unset(t_list **env, t_list **exp, t_cmd *cmd);
void	ms_env(t_list *env);
void	free_lst(t_list *lst);
void	free_all();
int		build_ins(t_cmd *cmd);

int		executer(t_cmd *cmd);

#endif