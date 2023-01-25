#include "../include/minishell.h"

//calls the builtin function for execution
int	call_builtin(char **argv, char *command)
{
	int	argc;
	int	builtin_cmd;

	argc = count_argc(argv);
	builtin_cmd = 0;
	if (!ft_strcmp(command, "echo"))
	{
		builtin_cmd = echo(argc, argv);
	}
	if (!ft_strcmp(command, "cd"))
		builtin_cmd = cd();
	if (!ft_strcmp(command, "pwd"))
		builtin_cmd = pwd();
	if (!ft_strcmp(command, "exit"))
		builtin_cmd = ft_exit();
	return (builtin_cmd);
}

int call_cmd(char **argv)
{
	int argc;
	int builtin_cmd;
	builtin_cmd = 0;
	argc = count_argc(argv);
	
	builtin_cmd = getenv_ls(argc, argv);
	return (builtin_cmd);	
}

//calls the a propreate function to execute
int	execute(t_mini *mini)
{
	char	**argv;
	t_token	*tok;
	t_token	*command;

	tok = mini->tokens;
	while (tok)
	{
		command = tok;
		argv = convert_argv(command);
		tok = tok->next;
		while (tok && tok->type == ARG)
			tok = tok->next;
		call_pipe_redirect(mini, command, tok);
		if (command->type == BUILTIN)
			mini->execute_code = call_builtin(argv, command->str);
		else if (command->type == CMD)
		{
			printf("arg is %s\n\n", *argv);
			mini->execute_code = call_cmd(argv);
			
		}
	}
	return (0);
}

