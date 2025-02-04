
#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/libft.h"
#include <stdio.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h> //readline
#include <unistd.h> //getcwd, chdir
#include <stdlib.h> //exit malloc
#include <string.h>
#include <errno.h>  //for errno
#include <limits.h> //for PATH_MAX

typedef enum s_type{
    
    PIPE,
    REDIR,
    WORD,
    EXPANDED, //? maybe will be neded in executer, ask miguel
    APPEND, // >>
    INFILE, // <
    OUTFILE,// >
    HERE_DOC, // <<
    COMMAND,
    COMMAND_ARGS,

}t_type;

typedef struct s_token
{
    t_type type;
    char *str;
    struct s_token *prev;
    struct s_token *next;
}t_token;

typedef struct s_redir
{
    t_type type;
    char *str;
}   t_redir;
typedef struct s_cmd
{
    int             hdoc_pipe[2];

    int             fd_in;
    int             fd_out; 
    int             pipe[2];
    int             pid;

	char			*path;
	char			**arg;
    int             n_arg;

	t_redir			**red_out;
	t_redir			**red_in;
   
}	t_cmd;

typedef struct s_shell
{
	char *readline;

	t_token *tokens;
	t_cmd   **cmd;

	t_list *env;
	t_list  *exp;

	//int pipe_count;
	int exit_status; // ? para eu poder expandir $?

	//int fd_in;
	//int fd_out;


}t_shell;


//void	ft_putendl_fd(char *s, int fd);
t_shell *get_shell(void);
void check_main_args(int ac);

#endif