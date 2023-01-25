#include "../include/minishell.h"

//get builtin command
int	builtin_cmd(char *token)
{
	if (!ft_strcmp(token, "echo")
		|| !ft_strcmp(token, "cd")
		|| !ft_strcmp(token, "pwd")
		|| !ft_strcmp(token, "export")
		|| !ft_strcmp(token, "unset")
		|| !ft_strcmp(token, "env")
		|| !ft_strcmp(token, "exit")
		|| !ft_strcmp(token, "history"))
		return (1);
	return (0);
}

//to detect delimiter tokens
int	delim_token(char *token)
{
	if (!ft_strcmp(token, ">"))
		return (TRUNC);
	if (!ft_strcmp(token, ">>"))
		return (APPEND);
	if (!ft_strcmp(token, "<"))
		return (INPUT);
	if (!ft_strcmp(token, "<<"))
		return (HEREDOC);
	if (!ft_strcmp(token, "|"))
		return (PIPE);
	return (0);
}

int	path_with_command(char *token)
{
	if (!ft_strcmp(token, "ls")
		|| !ft_strcmp(token, "cat")
		|| !ft_strcmp(token, "wc"))
		return (CMD);
	return (0);
}

//to get the token types from input
int	token_type(t_mini *mini, char *token)
{
	if (delim_token(token))
	{
		mini->cmd = 1;
		return (delim_token(token));
	}
	else if (builtin_cmd(token))
	{	
		mini->cmd = 0;
		return (BUILTIN);
	}
	else if (path_with_command(token))
	{
		mini->cmd = 0;
		return (CMD);
	}
	if (!mini->cmd)
	{
		return (ARG);
		printf("able to arg");
	}
	return (0);
}

//create new token list
t_token	*new_token(t_mini *mini, char *data)
{
	t_token	*res;

	res = (t_token *)malloc(sizeof(t_token));
	res->str = ft_strdup(data);
	res->type = token_type(mini, data);
	res->prev = 0;
	res->next = 0;
	return (res);
}

//addes a token to the end of the list
void	token_addend(char *data, t_mini *mini)
{
	t_token	*tok;
	t_token	*temp;

	tok = mini->tokens;
	while (tok->next)
		tok = tok->next;
	temp = new_token(mini, data);
	tok->next = temp;
	tok->next->prev = tok;
}