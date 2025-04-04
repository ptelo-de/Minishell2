/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 23:53:27 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/04/01 19:01:13 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h> //readline
# include <unistd.h> //getcwd, chdir
# include <stdlib.h> //exit malloc
# include <string.h>
# include <errno.h>  //for errno
# include <limits.h> //for PATH_MAX
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>

# define PRIVATE_PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin\
:/usr/bin:/sbin:/bin"

typedef enum s_type
{
	PIPE,
	REDIR,
	WORD,
	QUOTE,
	DOLLAR,
	APPEND,
	INFILE,
	OUTFILE,
	HERE_DOC,
	COMMAND,
	COMMAND_ARGS,
}	t_type;

typedef struct s_token
{
	t_type			type;
	char			*str;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_type	type;
	t_type	expansion_rule;
	char	*str;
}	t_redir;

typedef struct s_cmd
{
	t_redir			**here;

	int				fd_in;
	int				fd_out;
	int				pipe[2];
	t_redir			**red;
	int				out_error;

	int				pid;

	char			**arg;
	int				n_arg;
}	t_cmd;

typedef struct s_shell
{
	char	*readline;

	t_token	*tokens;
	t_cmd	**cmd;

	t_list	*env;
	t_list	*exp;

	int		exit_status;

	int		here_pipe[2];

	char	*private_path;
}	t_shell;

t_shell	*get_shell(void);
void	check_main_args(int ac);

//signals/
void	interactive_mode(void);
void	ignore_signal(int signal);
void	here_sigint(void);
void	executer_mode(void);

#endif