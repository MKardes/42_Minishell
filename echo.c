/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 06:18:30 by mkardes           #+#    #+#             */
/*   Updated: 2022/09/18 10:10:56 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	checkput(char *str)
{
	printf("%s ",str);
}

void	echo(void)
{
	int	i;
	int	n_chc;

	n_chc = 0;
	if (shell_g.all[shell_g.p][i][0] == '-')
	{
		if (shell_g.all[shell_g.p][i][1] == 'n')
			n_chc = 1;
		else
		{
			ft_error ("echo", "Undifened option");
			return ;
		}
	}
	i = 1;
	while (i + n_chc  < shell_g.in_pipe[shell_g.p] - 1)
	{
		checkput(shell_g.all[shell_g.p][i + n_chc]);
		i++;
	}
	checkput(shell_g.all[shell_g.p][i]);
	if (n_chc != 1)
		printf("\n");
}
