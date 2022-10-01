/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 00:21:43 by mkardes           #+#    #+#             */
/*   Updated: 2022/10/01 00:30:00 by mkardes          ###   ########.fr       */
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
	char	*name;
	char	*s;

	(void)av;
	if (ac != 1)
		return (0);
	g_shell.mpipe = (int *)malloc(sizeof(int) * 2);
	g_shell.env = ft_strddup(env);
	g_shell.info = malloc(10000);
	g_shell.p_cnt = 0;
	g_shell.prompt = ft_strdup("<\033[0;92m Shell\033[0;39m > ");
	pipe(g_shell.mpipe);
	signal(SIGINT, sig_int);
	minishell_put();
	while (1)
	{
		g_shell.p = 0;
		if (g_shell.line)
		{
			free(g_shell.line);
			g_shell.line = NULL;
		}
		g_shell.line = readline(g_shell.prompt);
		if (!g_shell.line)
		{
			printf("exit\n");
			exit(0);
		}
		if (!g_shell.line[0])
            continue ;
		add_history(g_shell.line);
		parsing();
		//sign_chc();
		start();
		//pipe_sign_chc();
		myfree();
	}
	return (0);
}
