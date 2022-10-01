/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 10:56:25 by mkardes           #+#    #+#             */
/*   Updated: 2022/09/22 18:11:57 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	operator_chc(void)
{
	int	i;

	i = 1;
	while (i < g_shell.in_pipe[g_shell.p])
	{
		if (g_shell.all[g_shell.p][i][0] == '-')
		{
			ft_error(g_shell.all[g_shell.p][0], "Undifened option");
			return (0);
		}
		i++;
	}
	return (1);
}

void	myfree(void)
{
	int	i;
	int	j;

	i = 0;
	while (i <= g_shell.p_cnt)
	{
		j = 0;
		while (j < g_shell.in_pipe[i])
		{
			free(g_shell.all[i][j]);
			j++;
		}
		free(g_shell.all[i]);
		i++;
	}
	//g_shell.info = ft_calloc(ft_strlen(g_shell.info), 1);
	free(g_shell.in_pipe);
	free(g_shell.all);
	g_shell.p_cnt = 0;
}

void	my_exit(void)
{
	if (!operator_chc())
		return ;
	if (g_shell.all[g_shell.p][1])
		exit(ft_atoi(g_shell.all[g_shell.p][1]) % 256);
	exit(0);
}

void	ft_error(char *command, char *msg)
{
	printf("%s: %s\n",command, msg);
}
