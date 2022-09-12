#include "minishell.h"

void	put_envs(void)
{
	int	i;

	i = 0;
	while (shell_g.env[i])
	{
		printf("%s\n", shell_g.env[i]);
		i++;
	}
}

void	parsing(char *s)
{
	int	i;

	i = 0;
	while ()
	{
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	char	*name;
	char	*s;

	if (ac != 2)
		return (0);
	shell_g.env = env;
	name = ft_strdup("<\033[0;92m Shell\033[0;39m > ");
	while(1)
	{
		s = readline(name);
		parsing(s);
	}
	return (0);
}
