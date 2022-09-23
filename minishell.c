/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 00:21:43 by mkardes           #+#    #+#             */
/*   Updated: 2022/09/22 20:36:37 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	shell_g;

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
	shell_g.mpipe = (int *)malloc(sizeof(int) * 2);
	shell_g.env = ft_strddup(env);
	shell_g.info = malloc(10000);
	shell_g.p_cnt = 0;
	shell_g.prompt = ft_strdup("<\033[0;92m Shell\033[0;39m > ");
	pipe(shell_g.mpipe);
	signal(SIGINT, sig_int);
	minishell_put();
	while (1)
	{
		shell_g.p = 0;
		if (shell_g.line)
		{
			free(shell_g.line);
			shell_g.line = NULL;
		}
		shell_g.line = readline(shell_g.prompt);
		if (!shell_g.line)
		{
			printf("exit\n");
			exit(0);
		}
		if (!shell_g.line[0])
            continue ;
		add_history(shell_g.line);
		parsing();
		//sign_chc();
		start();
		//pipe_sign_chc();
		myfree();
	}
	return (0);
}
