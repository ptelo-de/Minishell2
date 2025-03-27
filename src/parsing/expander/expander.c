#include "parsing.h"

void expand_quote(int *i, char **update, char *src, char quote_char)
{
	int len;

	len = 0;
	while (src && src[++len])
	{
		if (quote_char == '\'')
		{
			if (src[len] == '\'')
				break;
			update_str(update, src, len, 1);
		}
		if (quote_char == '\"')
		{
			if (src[len] == '$' && src[len + 1] != '\"')
				process_dollar(&len, src + len, update);
			else if (src[len] == '$' && src[len + 1] == '\"')
				update_str(update, src, len++, 1);
			if (src[len] != '\"')
				update_str(update, src, len, 1);
			else if (src[len] == '\"')
				break;
		}
	}
	*i += len;
}

void	expand_node(t_token **tmp, char	*update)
{
	int i;

	i = 0;
	while ((*tmp)->str && (*tmp)->str[i])
	{
		if ((*tmp)->str[i] == '\'' || (*tmp)->str[i] == '\"')
		{
			(*tmp)->type = QUOTE;
			expand_quote(&i, &update, (*tmp)->str + i, (*tmp)->str[i]);
			i++;
		}
		else if ((*tmp)->str[i] == '$')
		{
			(*tmp)->type = DOLLAR;
			process_dollar(&i, (*tmp)->str + i, &update);
		}
		else
			update_str(&update, (*tmp)->str, i++, 1);
	}
	if ((*tmp)->str)
		free((*tmp)->str);
	if (update)
		(*tmp)->str = update;
	else
		(*tmp)->str = NULL;
}

void expander(void)
{
	t_token *tmp;

	if (!get_shell() || !get_shell()->tokens)
		return;
	tmp = get_shell()->tokens;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			expand_node(&tmp, NULL);
		}
		tmp = tmp->next;
	}
	clear_empty_token();
}
