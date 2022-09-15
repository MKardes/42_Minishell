/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 00:21:43 by mkardes           #+#    #+#             */
/*   Updated: 2022/09/16 01:35:22 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	myfree(void)
{
	int	i;
	int	j;

	free(shell_g.line);
	i = 0;
	while (i <= shell_g.p_cnt)
	{
		j = 0;
		while (j < shell_g.in_pipe[i])
		{
			free(shell_g.all[i][j]);
			j++;
		}
		free(shell_g.all[i]);
		i++;
	}
	free(shell_g.in_pipe);
	free(shell_g.all);
}

void	a(int sig)
{
	if (sig == SIGINT)
		printf("\n%s", shell_g.prompt);
}

int	main(int ac, char **av, char **env)
{
	char	*name;
	char	*s;

	if (ac != 1)
		return (0);
	shell_g.env = env;
	shell_g.p_cnt = 0;
	shell_g.prompt = ft_strdup("<\033[0;92m Shell\033[0;39m > ");
	signal(SIGINT, a);
	while (1)
	{
		shell_g.line = readline(shell_g.prompt);
		if (!shell_g.line)
		{
			printf("exit");
			exit(0);
		}
		add_history(shell_g.line);
		parsing(shell_g.line);
		myfree();
		shell_g.p_cnt = 0;
	}
	return (0);
}
