#ifndef EXECUTER_H
# define EXECUTER_H

# include "minishell.h"

void	close_all_fd_red();
void	free_arr(char **arr);
char	*trim_prefix(char *str, char *prefix);
t_list	*get_env(char **envp);
char	*put_double_quotes(char *str);
int		is_longer(char	*str1, char	*str2);
int		is_repeated(char *str, char **env_order);
char	*get_smallest(char **env_order, char **envp);
int		arr_len(char **arr);
char	 **alpha_order(char **envp);
t_list	*get_exp(char **envp);
int		flag_n(char *arg);
int		ms_echo(t_cmd *cmd);
void	update_pwd_env(char *path, t_list **env);
void	update_pwd_exp(char *path, t_list **exp);
char	*join_all_args(t_cmd *cmd);
int		ms_cd(t_list **env, t_list **exp, t_cmd *cmd);
int		ms_pwd();
int		has_equal(char *var);
void	put_export_mid_end(t_list **exp, char *var, t_list *new_node);
void	put_export(t_list **exp, char *var);
char	*trim_value(char *var);
int		update_lst(t_list **lst, char *var, int b);
void	print_exp(t_list *exp);
int		arg_valid(char *arg);
int		ms_export(t_list **env, t_list **exp, t_cmd *cmd);
void	delete_var(t_list **lst, char *var);
int		delete_var_no_equal(t_list **lst, char *var_no_equal);
int		ms_unset(t_list **env, t_list **exp, t_cmd *cmd);
int		ms_env(t_list *env);
int		str_isdigit(char *str);
void	free_all();
void	ms_exit(t_shell **shell, t_cmd *cmd, int here);
void	free_lst(t_list *lst);
int		build_ins(t_cmd *cmd);

//int		manage_hd(t_cmd *cmd);
void	manage_hd(t_shell *shell);
int		last_is_infile(t_cmd *cmd);
void	manage_redir(t_shell **shell);
void	executer();
//int		manage_infile(t_shell **shell, t_cmd *cmd);
int		get_fd_infile(char *infile);
//int		fd_last_in_red(int fd_hd, t_cmd *cmd);
int		error_open_outfile(int fd_outfile, char *name_outfile);
//int		fd_last_out_red(t_cmd *cmd);
char	**find_path(char **envp);
char	*increase_shlvl(char *envp_i);
char	*set_shlvl(char *envp_i);
char	*create_path(char *function, char **envp);
void	error_exec(char *path, char **envp);
void	exec_command(char **args, char **envp);
char	**make_env_arr(t_list *env);
//int		executer(t_cmd *cmd);

void exec_mode(void);

#endif