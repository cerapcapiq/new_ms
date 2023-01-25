#include "../include/minishell.h"

int cd(void)
{
	chdir("..");
	return (0);
}

int ft_exit(void)
{
	exit(0);
}

int	pwd(void)
{
	char	*path;

	path = getcwd(NULL, 1024);
	if (!path)
	{
		free(path);
		return (1);
	}
	printf("%s\n", path);
	free(path);
	return (0);
}