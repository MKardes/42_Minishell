/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_cmnds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 09:45:09 by mkardes           #+#    #+#             */
/*   Updated: 2022/09/22 17:09:18 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ch_wd(char *dest)
{
	char	*var;
	int		i;
	char	*wd;

	i = 0;
	wd = getcwd(NULL, 1024);
	while (shell_g.env[i])
	{
		var = ft_substr(shell_g.env[i], 0, 3);
		if (ft_strstr(var, "PWD"))
		{
			free(shell_g.env[i]);
			free(var);
			shell_g.env[i] = ft_strjoin("PWD=", wd);
			break ;
		}
		free(var);
		i++;
	}
	free(wd);
}

void	cd(void)
{
	char			*dest;

	if (!operator_chc())
		return ;
	dest = ft_strdup(shell_g.all[shell_g.p][1]);
	if (chdir(dest) == -1)
		printf("cd: directory couldn't be changed\n");
	else
		ch_wd(dest);
	free(dest);
}

void	pwd(void)
{
	int		i;
	char	*s;
	char	*a;
	int		pid;

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
