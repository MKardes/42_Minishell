/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 00:01:54 by mkardes           #+#    #+#             */
/*   Updated: 2022/11/10 17:00:54 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**command__chc(int p)
{
	char	**ptr;

	ptr = malloc(sizeof(char **));
	g_shell.in_pipe[p] = 0;
	return (ptr);
}

int	command_chc(void)
{
	if (g_shell.in_pipe[g_shell.p] == 0)
	{
		ft_error("bash", "pipe usage error");
		return (1);
	}
	return (0);
}

int	operator_chc(void)
{
	int	i;

	i = 1;
	while (i < g_shell.in_pipe[g_shell.p])
	{
		if (g_shell.all[g_shell.p][i][0] == '-')
		{
			ft_error(g_shell.all[g_shell.p][0], "Undefined option");
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_error(char *command, char *msg)
{
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
	if (msg[0] == 'U')
		g_shell.exit_status = 2;
	if (msg[0] == 'w')
		g_shell.exit_status = 1;
	if (msg[0] == '<')
		g_shell.exit_status = 5;
}
