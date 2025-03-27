#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

// debug/printing_functions.c
void print_tokens(void);
void print_cmd_array(void);

//../parsing/cmd_array_build.c
t_redir **get_red(t_token	*token);
void	get_args(t_token *token, t_cmd *cmd);
t_cmd *get_next_cmd(t_token *token);
void get_next_cmd_token(t_token **token);
int init_cmd(void);

//../parsing/expander/expansion_utils.c
size_t safe_strlen(const char *s);
char	*ms_strjoin(char const *s1, char const *s2);
void restore_empty_str(void);
void clear_empty_token(void);
void update_str( char **update, char *src, int start, int len);

//../parsing/expander/expander.c
void expand_quote(int *i, char **update, char *src);
void	expand_node(t_token **tmp, char *update); //+ de 25
void expander(void);

//../parsing/expander/process_dollar.c
char *get_value(char *name);
void exit_status_expander( char **update);
void	process_dollar(int *len, char *src, char **update);

//../parsing/frees/free_atributes.c
void    free_tokens(void);
void free_atributes(void);

//../parsing/frees/free_cmds.c
void free_cmd_redir(t_cmd **cmd);
void free_cmds(void);

//../parsing/lexer/lexer.c
int quotes_check(void);
int lexer(void);

//../parsing/lexer/skip.c
void white_space_skip(int *i);
int quote_skip(int *i);
void word_skip(int *i);
void redir_skip(int *i);

//../parsing/lexer/token_utils.c
void add_token(int start, int len, t_type type);
t_token	*tokenlast(t_token *first);

//syntax_error.c
int syntax_check(void);

//cmd_array.c
int init_cmd(void);

//here
int hereDoc(char *del, t_type expantion_rule);

//here_expander.c
void	here_expander(char **line);

#endif