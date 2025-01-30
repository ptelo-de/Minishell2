#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

// debug/printing_functions.c
void print_tokens(void);
void print_cmd_array(void);

//lexer
void white_space_skip(int *i);
int quote_skip(int *i);
void word_skip(int *i);
int lexer(void);

//token_utils1.c
void add_token(int start, int len, t_type type);
t_token	*tokenlast(t_token *first);
void    free_tokens(void);
void free_atributes(void);

//syntax_error.c
int syntax_check(void);


//expansion_utils.c
void clear_empty_token(void);
char	*ms_strjoin(char const *s1, char const *s2);
void update_str( char **update, char *src, int start, int len);
//expantion.c

void    expander(void);
int has_dollar(const char *str);
void remove_double_quotes(t_token **tmp);
void remove_single_quote(t_token **tmp);

//edit_token.c
void skip_till_dollar(int *i, char *s);
char *get_value(char *name);
void change_str(t_token **tmp, int *i, int j, char *value);
int check_first_char(int *i, t_token **tmp, int j);
void handle_one_dollar(int *i, t_token **tmp);

//cmd_array.c
int init_cmd(void);

#endif