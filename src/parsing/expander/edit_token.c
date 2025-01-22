
#include "parsing.h"

char *get_value(char *name)
{
    t_shell *shell;
    char **env;
    size_t name_len;

    if (!name || !(shell = get_shell()))
    {
        return NULL;
    }
    env = shell->env;
    name_len = ft_strlen(name);

    while (env && *env)
	{
        if (ft_strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
		{
            return (*env + name_len + 1);
        }
        env++;
    }
    return NULL;
}

void skip_till_dollar(int *i, char *s) {
    if (!s || !i) {
        return;
    }
    while (s[*i] && s[*i] != '$') {
        (*i)++;
    }
}

size_t safe_str_len(char *s)
{
	int i;

	if (!s) 
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);	
}

void change_str(t_token **tmp, int *i, int j, char *value)
{
    char *new_str;
    int k, l;

    if (!tmp || !*tmp)
        return;

    new_str = ft_calloc(1, sizeof(char) * (ft_strlen((*tmp)->str) - (j - *i) + ft_strlen(value) + 1));
    if (!new_str)
	{
        free_tokens();
        return;
    }
    k = 0;
    while (k < *i)
	{
        new_str[k] = (*tmp)->str[k];
        k++;
    }
    l = 0;
    while (value[l]) {
        new_str[k + l] = value[l];
        l++;
    }

    k += l;
    l = j;
    while ((*tmp)->str[l]) {
        new_str[k++] = (*tmp)->str[l++];
    }
    free((*tmp)->str);
    (*tmp)->str = new_str;
    *i += ft_strlen(value) - 1;
}

int check_first_char(int *i, t_token **tmp, int j)
{
    if ((*tmp)->str[j] == '?')
	{
        change_str(tmp, i, j + 1, "EXIT STATUS");
        return 1;
    }
    if ((*tmp)->str[j] == '0')
	{
        change_str(tmp, i, j + 1, "bash");
        return 1;
    }
    return 0;
}

void handle_one_dollar(int *i, t_token **tmp)
{
    int j;
    char *value;
    char *name;

    if (!i || !tmp || !*tmp || !(*tmp)->str) {
        return;
    }
    skip_till_dollar(i, (*tmp)->str);
    j = *i + 1;
    if (check_first_char(i, tmp, j)) {
        return;
    }
    while (ft_isalnum((*tmp)->str[j]) || (*tmp)->str[j] == '_')
        j++;
    name = ft_substr((*tmp)->str, *i + 1, j - *i - 1);
    value = get_value(name);
    free(name);
    if (value) {
        change_str(tmp, i, j, value);
    } else {
        *i = j;
    }
}
