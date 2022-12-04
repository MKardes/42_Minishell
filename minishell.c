/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 00:21:43 by mkardes           #+#    #+#             */
/*   Updated: 2022/11/11 10:06:18 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_put(void)
{
	printf("\033[0;93m\t__    __  ___  __    ___  ___      _____  "\
			"___   ___  ________  ________  ___\n");
	printf("\t| \\  / |  | |  | \\   | |  | |     / ___|  | |   | "\
			"|  | _____|  | _____|  | |\n");
	printf("\t|  \\/  |  | |  | |\\  | |  | |     \\ \\     | |___"\
			"| |  | |___    | |___    | |\n");
	printf("\t| |\\/| |  | |  | | \\ | |  | |       \\ \\   | ____"\
			"_ |  | ___|    | ___|    | |\n");
	printf("\t| |  | |  | |  | |  \\| |  | |     ___/ /  | |   | |"\
			"  | |_____  | |_____  | |______\n");
	printf("\t|_|  |_|  |_|  |_|   \\_|  |_|    |____/   |_|   |_|"\
			"  |______|  |______|  |_______|\n\033[0;39m");
}

int	main(int ac, char **av, char **env)
{
	int		i;

	(void)av;
	if (ac != 1)
		return (0);
	g_shell.env = ft_strddup(env);
	g_shell.p_cnt = 0;
	g_shell.exit_status = 0;
	g_shell.prompt = ft_strdup("<\033[0;92m Shell\033[0;39m > ");
	g_shell.save_fd = (int *)ft_calloc(2, sizeof(int));
	g_shell.heredocpipe = (int *)malloc(sizeof(int) * 2);
	signal(SIGINT, sig_int);
	minishell_put();
	while (1)
	{
		pipe(g_shell.heredocpipe);
		g_shell.p = 0;
		if (g_shell.line)
		{
			free(g_shell.line);
			g_shell.line = NULL;
		}
		g_shell.line = readline(g_shell.prompt);
		if (g_shell.line == NULL)
		{
			ft_putstr_fd("\b\bexit\n", 1);
			exit(0);
		}
		if (g_shell.line[0] == '\0')
		{
			close(g_shell.heredocpipe[0]);
			close(g_shell.heredocpipe[1]);
			continue ;
		}
		if (g_shell.line[0] == '\n')
		{
			printf("aa");
		}
		add_history(g_shell.line);
		parsing();
		g_shell.mpipe = (int **)malloc(sizeof(int *) * g_shell.p_cnt + 1);
		g_shell.mpipe[g_shell.p_cnt] = NULL;
		i = 0;
		while (i < g_shell.p_cnt)
		{
			g_shell.mpipe[i] = (int *)malloc(sizeof(int) * 2);
			pipe(g_shell.mpipe[i]);
			i++;
		}
		heredoc_fill();
		start();
		myfree();
	}
	return (0);
}
