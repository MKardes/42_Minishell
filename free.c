/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 10:56:25 by mkardes           #+#    #+#             */
/*   Updated: 2022/09/18 10:20:14 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	operator_chc(void)
{
	int	i;

	i = 1;
	while (i < shell_g.in_pipe[shell_g.p])
	{
		if (shell_g.all[shell_g.p][i][0] == '-')
		{
			ft_error("export", "Undifened option");
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
	shell_g.p_cnt = 0;
}

void	my_exit(void)
{
	//if (ft_atoi())
	exit(0);
}

void	ft_error(char *command, char *msg)
{
	printf("%s: %s\n",command, msg);
}