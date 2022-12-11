/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:04:25 by mkardes           #+#    #+#             */
/*   Updated: 2022/11/10 17:16:45 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**arg_add(char **arg, char *str)
{
	char	**new;
	int		i;

	i = 0;
	while (arg[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	new[i + 1] = NULL;
	i = 0;
	while (arg[i])
	{
		new[i] = arg[i];
		i++;
	}
	new[i] = str;
	free (arg);
	return (new);
}	

void	get_output(void)
{
	if (g_shell.p != g_shell.p_cnt)
	{
		dup2(g_shell.mpipe[g_shell.p][1], 1);
		close(g_shell.mpipe[g_shell.p][1]);
		close(g_shell.mpipe[g_shell.p][0]);
	}
	if (g_shell.p != 0)
	{
		dup2(g_shell.mpipe[g_shell.p - 1][0], 0);
		close(g_shell.mpipe[g_shell.p - 1][0]);
		close(g_shell.mpipe[g_shell.p - 1][1]);
	}
}
