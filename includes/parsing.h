/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptelo-de <ptelo-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 23:46:14 by ptelo-de          #+#    #+#             */
/*   Updated: 2025/03/29 23:52:20 by ptelo-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

// debug/printing_functions.c
void	print_tokens(void);
void	print_cmd_array(void);

//../parsing/cmd_array_build/get_args.c
int		is_arg(t_token *token);
void	assign_args(t_token	*tokens, char	***args);
void	get_args(t_token *token, t_cmd *cmd);

//../parsing/cmd_array_build/get_redirs.c
void	assign_redirs(t_token	*token, t_redir	***redir);
t_redir	**get_red(t_token	*token);

//../parsing/cmd_array_build/init_cmd.c
t_cmd	*get_next_cmd(t_token *token);
void	get_next_cmd_token(t_token **token);
int		count_cmds(t_token	*tokens);
int		init_cmd(void);

//../parsing/expander/expansion_utils.c
size_t	safe_strlen(const char *s);
char	*ms_strjoin(char const *s1, char const *s2);
void	restore_empty_str(void);
void	clear_empty_token(void);
void	update_str( char **update, char *src, int start, int len);

//../parsing/expander/expander.c
void	expand_quote(int	*i, char **update, char *src, char quote_char);
void	expand_node(t_token **tmp, char *update);
void	expander(void);

//../parsing/expander/process_dollar.c
char	*get_value(char *name);
void	exit_status_expander( char **update);
void	expand_standard_dollar_format(int	\
**pointer_add, char	*src, char **update);
void	process_dollar(int	*len, char *src, char **update);

//../parsing/frees/free_atributes.c
void	free_tokens(void);
void	free_atributes(void);

//../parsing/frees/free_cmds.c
void	free_cmd_redir(t_cmd **cmd);
void	free_cmds(void);

//../parsing/lexer/lexer.c
int		quotes_check(void);
int		lexer(void);

//../parsing/lexer/skip.c
void	white_space_skip(int	*i);
int		quote_skip(int	*i);
void	word_skip(int	*i);
void	redir_skip(int	*i);

//../parsing/lexer/token_utils.c
void	add_token(int start, int len, t_type type);
t_token	*tokenlast(t_token *first);

//syntax_error.c
int		syntax_check(void);

//cmd_array.c
int		init_cmd(void);

//here
int		here_doc(char *del, t_type expansion_rule);

//here_expander.c
void	here_expander(char **line);

#endif