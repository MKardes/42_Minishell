/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environmentals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:58:40 by mkardes           #+#    #+#             */
/*   Updated: 2022/09/16 15:01:40 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(char *s)
{
	int	i;

	i = 0;
	while (shell_g.env[i])
	{
		printf("%s", shell_g.env[i]);
		i++;
	}
}

void	sig_int(int sig)
{
	if (sig == SIGINT)
		printf("\n%s", shell_g.prompt);
}
