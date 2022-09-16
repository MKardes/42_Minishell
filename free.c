/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 10:56:25 by mkardes           #+#    #+#             */
/*   Updated: 2022/09/16 10:56:27 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	myfree(void)
{
	int	i;
	int	j;

	free(shell_g.line);
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
