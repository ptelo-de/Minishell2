
#include "parsing.h"
size_t safe_strlen(const char *s)
{
	int i;

	if (!s) 
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);	
}

char	*ms_strjoin(char *s1, char *s2)
{
	char	*join;
	size_t	i;
	size_t	j;

	join = malloc((safe_strlen(s1) + safe_strlen(s2) + 1) * (sizeof(char)));
	if (join == 0)
		return (0);
	i = 0;
	while (s1 && s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = 0;
	return (join);
}
void clear_empty_token(void)
{
	t_shell *shell;
	t_token *tmp;
	t_token *next;

	shell = get_shell();
	tmp = shell->tokens;
	while (tmp)
	{
		next = tmp->next;
		printf("tmp str:%s\n", tmp->str);
		if (!tmp->str || !tmp->str[0])
		{
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			else
				shell->tokens = tmp->next;

			if (tmp->next)
				tmp->next->prev = tmp->prev;

			free(tmp);
		}
		tmp = next;
	}
}

