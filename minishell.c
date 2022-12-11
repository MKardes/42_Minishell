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
			"___   ___  ________  ___        ___\n");
	printf("\t| \\  / |  | |  | \\   | |  | |     / ___|  | |   | "\
			"|  | _____|  | |        | |\n");
	printf("\t|  \\/  |  | |  | |\\  | |  | |     \\ \\     | |___"\
			"| |  | |___    | |        | |\n");
	printf("\t| |\\/| |  | |  | | \\ | |  | |       \\ \\   | ____"\
			"_ |  | ___|    | |        | |\n");
	printf("\t| |  | |  | |  | |  \\| |  | |     ___/ /  | |   | |"\
			"  | |_____  | |______  | |______\n");
	printf("\t|_|  |_|  |_|  |_|   \\_|  |_|    |____/   |_|   |_|"\
			"  |______|  |_______|  |_______|\n\033[0;39m");
}

void	fill_and_put(char **av, char **env)
{
	(void)av;
	g_shell.env = ft_strddup(env);
	declare_init();
	g_shell.p_cnt = 0;
	g_shell.exit_status = 0;
	g_shell.prompt = ft_strdup("< Shell > ");
	g_shell.save_fd = (int *)ft_calloc(2, sizeof(int));
	g_shell.heredocpipe = (int *)malloc(sizeof(int) * 2);
	minishell_put();
	signal(SIGINT, sig_int);
}

void	open_pipes(void)
{
	int	i;

	g_shell.mpipe = (int **)malloc(sizeof(int *) * g_shell.p_cnt + 1);
	g_shell.mpipe[g_shell.p_cnt] = NULL;
	i = 0;
	while (i < g_shell.p_cnt)
	{
		g_shell.mpipe[i] = (int *)malloc(sizeof(int) * 2);
		pipe(g_shell.mpipe[i]);
		i++;
	}
}

void	shell_exit(void)
{
	ft_putstr_fd("\b\bexit\n", 1);
	exit(0);
}

int	main(int ac, char **av, char **env)
{
	if (ac != 1)
		return (0);
	fill_and_put(av, env);
	while (1)
	{
		if (g_shell.line)
		{
			free(g_shell.line);
			g_shell.line = NULL;
		}
		g_shell.line = readline(g_shell.prompt);
		if (g_shell.line == NULL)
			shell_exit();
		if (g_shell.line[0] == '\0')
			continue ;
		add_history(g_shell.line);
		parsing();
		if (heredoc_fill() != -1)
			start(0);
		myfree();
	}
	return (0);
}
