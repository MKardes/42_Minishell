/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 06:18:30 by mkardes           #+#    #+#             */
/*   Updated: 2022/10/26 19:38:39 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(void)
{
	int	i;
	int	n_chc;

	n_chc = 0;
	i = 1;
	if (g_shell.all[g_shell.p][i] && g_shell.all[g_shell.p][i][0] == '-')
	{
		if (g_shell.all[g_shell.p][i][1] == 'n')
			n_chc = 1;
		else
		{
			ft_error("echo", "Undefined option");
			return ;
		}
	}
	while (i + n_chc < g_shell.in_pipe[g_shell.p])
	{
		printf("%s", g_shell.all[g_shell.p][i + n_chc]);
		if (i + n_chc + 1 != g_shell.in_pipe[g_shell.p])
			printf(" ");
		i++;
	}
	if (n_chc != 1)
		printf("\n");
	g_shell.exit_status = 0;
}
