/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 10:56:25 by mkardes           #+#    #+#             */
/*   Updated: 2022/11/10 18:56:58 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	i = -1;
	while (g_shell.mpipe[++i])
		free(g_shell.mpipe[i]);
	free(g_shell.mpipe[i]);
	free(g_shell.mpipe);
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
