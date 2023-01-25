#include "../include/minishell.h"

int ft_cmd(char *str, char *lineptr)
{
	char *cmd = str;
	char *argv[] = {lineptr, NULL};
	char *env[] = {NULL};

	int status;
	int pid = fork();
	if (!pid)
	{
	if (execve(cmd, argv, env) == -1)
		return (-1);
	}
	waitpid(pid, &status, 0);
	return (2);
}

int getenv_ls(int argc, char **argv)
{
	char **split;
	int	i = 0;
	split = NULL;

	if (argc < 1)
		return (1);
	char *path = getenv("PATH");

	split = ft_split(path, ':');
	while (split[i] != NULL)
	{
		split[i] = ft_strjoin(split[i], "/");
		split[i] = ft_strjoin(split[i], argv[0]);
		if (ft_cmd(split[i], *argv) != -1)
		{
			break;
		}
		i++;
	}
	return (0);
}
