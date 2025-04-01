/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:41:36 by bde-luce          #+#    #+#             */
/*   Updated: 2025/04/01 19:02:28 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
void	free_all(void);
int		arg_valid(char *arg);

t_list	*get_env(char **envp);

char	*put_double_quotes(char *str);
t_list	*get_exp(char **envp);

int		ms_echo(t_cmd *cmd);
int		ms_unset(t_list **env, t_list **exp, t_cmd *cmd);

int		ms_cd(t_shell *shell, t_list **env, t_cmd *cmd);
int		ms_pwd(void);

int		ms_export(t_list **env, t_list **exp, t_cmd *cmd);

int		ms_exit(t_shell **shell, t_cmd *cmd);
int		build_ins(t_cmd *cmd);

int		infile_error(t_cmd *cmd);
int		error_open_outfile(int fd_outfile, char *name_outfile, t_cmd *cmd);
char	**make_env_arr(t_list *env);
int		is_build_in(t_cmd *cmd);

void	manage_hd(t_shell *shell);

int		last_is_infile(t_cmd *cmd);
int		get_fd_infile(char *infile);

void	manage_redir(t_shell **shell);

void	executer(t_shell *shell);

char	*create_path(char *function, char **envp);

void	close_all_fd_red(void);
void	handle_cmd_input(t_shell *shell, int i, int prev_pipe0);
void	handle_cmd_output_and_execute(t_shell *shell, int i, int prev_pipe0);

void	exec_mode(void);

#endif