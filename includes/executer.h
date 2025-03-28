#ifndef EXECUTER_H
# define EXECUTER_H

# include "minishell.h"

void	free_arr(char **arr);
char	*trim_prefix(char *str, char *prefix);
int		is_longer(char	*str1, char	*str2);
int		arr_len(char **arr);
int		print_and_return(char *message, int exit_status);

int		has_equal(char *var);
char	*get_var_name(char *var);
void	free_lst(t_list *lst);
void	free_all();

t_list	*get_env(char **envp);

char	*put_double_quotes(char *str);
t_list	*get_exp(char **envp);

int		ms_echo(t_cmd *cmd);
int		ms_unset(t_list **env, t_list **exp, t_cmd *cmd);

int		ms_cd(t_shell *shell, t_list **env, t_cmd *cmd);
int		ms_pwd();

int		ms_export(t_list **env, t_list **exp, t_cmd *cmd);

int		ms_exit(t_shell **shell, t_cmd *cmd);
int		build_ins(t_cmd *cmd);

int		infile_error(t_cmd *cmd);
int		error_open_outfile(int fd_outfile, char *name_outfile);
char	**make_env_arr(t_list *env);
int		is_build_in(t_cmd *cmd);

void	manage_hd(t_shell *shell);

void	manage_redir(t_shell **shell);

void	executer();

char	*create_path(char *function, char **envp);

void	handle_cmd_input(t_shell *shell, int i, int prev_pipe0);
void	handle_cmd_output_and_execute(t_shell *shell, int i, int prev_pipe0);

void exec_mode(void);

#endif