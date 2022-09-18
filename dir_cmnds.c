/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_cmnds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 09:45:09 by mkardes           #+#    #+#             */
/*   Updated: 2022/09/18 10:07:04 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(void)
{
	printf("cd\n");
}

void	pwd(void)
{
	int		i;
	char	*s;
	char	*a;

	i = 0;
	if (!operator_chc())
		return ;
	while (shell_g.env[i])
	{
		s = ft_fsplit(shell_g.env[i], '=');
		if (ft_strstr(s, "PWD"))
		{
			a = ft_strchr(shell_g.env[i], '=');
			printf("%s\n", ++a);
			free(s);
			break ;
		}
		free(s);
		i++;
	}
}
