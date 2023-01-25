#include "../include/minishell.h"


int ft_strlen(const char *str)
{
    int i = 0;
    while (str[i] != '\0')
    i++;
    return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[j++] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str[j++] = s2[i];
		i++;
	}
	str[j] = 0;
	return (str);
}

int	count_argc(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		++i;
	return (i);
}

void	call_pipe_redirect(t_mini *mini, t_token *command, t_token *tok)
{
	if (!command)
		return ;
	if (tok && tok->type == PIPE)
	{
		create_pipe(mini);
		tok = tok->next;
	}
}

//converts arguments into an array of strings
char	**convert_argv(t_token	*tokens)
{
	int		i;
	t_token	*tok;
	char	**res;

	i = 0;
	tok = tokens;
	while (tok && (tok->type == ARG || tok->type == BUILTIN
			|| tok->type == CMD))
	{
		i++;
		tok = tok->next;
	}
	if (!i)
		return (0);
	res = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	tok = tokens;
	while (tok && (tok->type == ARG || tok->type == BUILTIN
			|| tok->type == CMD))
	{
		res[i++] = ft_strdup(tok->str);
		tok = tok->next;
	}
	res[i] = 0;
	return (res);
}