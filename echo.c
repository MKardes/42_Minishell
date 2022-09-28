/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 06:18:30 by mkardes           #+#    #+#             */
/*   Updated: 2022/09/28 14:46:49 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (i + n_chc  < shell_g.in_pipe[shell_g.p])
	{
		printf("%s", shell_g.all[shell_g.p][i + n_chc]);
		if (i + n_chc + 1 != shell_g.in_pipe[shell_g.p])
			printf(" ");
		i++;
	}
	if (n_chc != 1)
		printf("\n");
}
