/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_cmnds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 09:45:09 by mkardes           #+#    #+#             */
/*   Updated: 2022/10/30 19:54:55 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ch_wd(char *old)
{
	int		i;
	int		j;
	char	*wd;
	char	*tmp;

	wd = getcwd(NULL, 1024);
	i = env_finder("PWD");
	j = env_finder("OLDPWD");
	if (j == -1)
	{
		tmp = ft_strjoin("OLDPWD=", old);
		env_add(tmp);
		free(tmp);
	}
	else
	{
		free(g_shell.env[j]);
		g_shell.env[j] = ft_strjoin("OLDPWD=", old);
	}
	free(g_shell.env[i]);
	g_shell.env[i] = ft_strjoin("PWD=", wd);
	free(old);
	free(wd);
}

char	*dir_sign(char *str, char c)
{
	char	*dest;

	if (c == '-')
	{
		dest = ft_strdup(ft_strchr(g_shell.env[env_finder("OLDPWD")], '=') + 1);
		return (dest);
	}
	else if (c == '~')
	{
		ft_strchr(g_shell.env[env_finder("HOME")], '=');
		dest = ft_strjoin((ft_strchr(g_shell.env
					[env_finder("HOME")], '=') + 1), str);
		return (dest);
	}
	return (NULL);
}

void	cd_error(char *dest, char *old)
{
	write(1, "cd: ", 4);
	perror("");
	free(old);
	free(dest);
	g_shell.exit_status = 1;
}

void	cd(void)
{
	char	*dest;
	char	*old;

	if ((g_shell.all[g_shell.p][1][0] == '-' && g_shell.all
	[g_shell.p][1][1] == ' ') || g_shell.all[g_shell.p][1][0] == '~')
	{
		dest = dir_sign((g_shell.all[g_shell.p][1] + 1),
				g_shell.all[g_shell.p][1][0]);
	}
	else if (!operator_chc())
		return ;
	else
		dest = ft_strdup(g_shell.all[g_shell.p][1]);
	old = getcwd(NULL, 1024);
	if (chdir(dest) == -1)
	{
		cd_error(dest, old);
		return ;
	}
	else
		ch_wd(old);
	free(dest);
	g_shell.exit_status = 0;
}

void	pwd(void)
{
	int		i;
	char	*s;
	char	*a;

	i = 0;
	if (!operator_chc())
		return ;
	while (g_shell.env[i])
	{
		s = ft_fsplit(g_shell.env[i], '=');
		if (ft_strstr(s, "PWD"))
		{
			a = ft_strchr(g_shell.env[i], '=');
			printf("%s\n", ++a);
			free(s);
			break ;
		}
		free(s);
		i++;
	}
	g_shell.exit_status = 0;
}
