/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:04:25 by mkardes           #+#    #+#             */
/*   Updated: 2022/10/29 15:43:10 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**arg_add(char **arg, char *str)
{
	char	**new;
	int	i;

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

void	finder(void)
{
	int	i;
	char	*tmp;
	char	*a;
	char	**s;

	i = env_finder("PATH");
	tmp = ft_strchr(g_shell.env[i], '=');
	a = ft_strdup(tmp + 1);
	tmp = ft_strjoin(a, ":./");
	s = ft_split(tmp, ':');
	free(tmp);
	free(a);
	i = 0;
	while (s[i])
	{
		tmp = ft_strjoin(s[i], "/");
		free(s[i]);
		s[i] = ft_strjoin(tmp, g_shell.all[g_shell.p][0]);
		free(tmp);
		i++;
	}
	i = 0;
	while (s[i])
	{
		if (execve(s[i], g_shell.all[g_shell.p], g_shell.env) != -1)
			break;
		i++;
	}
	ft_error(g_shell.all[g_shell.p][0], "command not found");
	exit(-1);
}

void	command_select(void)
{
	int	pid;
	int	a = 0;

	if (command_chc())
		return ;
	if (ft_strstr(g_shell.all[g_shell.p][0], "env"))
		env();
	else if (ft_strstr(g_shell.all[g_shell.p][0], "export"))
		my_export();
	else if (ft_strstr(g_shell.all[g_shell.p][0], "echo"))
		echo();
	else if (ft_strstr(g_shell.all[g_shell.p][0], "cd"))
		cd();
	else if (ft_strstr(g_shell.all[g_shell.p][0], "pwd"))
		pwd();
	else if (ft_strstr(g_shell.all[g_shell.p][0], "exit"))
		my_exit();
	else if (ft_strstr(g_shell.all[g_shell.p][0], "unset"))
		my_unset();
	else
	{
		if (g_shell.p_cnt == 0)
		{
			pid = fork();
			if (pid == 0)
				finder();
			else
			{
				waitpid(pid, &a, 0);
				printf(".\t%d\t.\n",a / 256);
			}
		}
		else
			finder();
	}
}

void	start(void)
{
	int	pid;

	if (g_shell.p_cnt == 0)
		command_select();
	while (g_shell.p_cnt != 0 && g_shell.p <= g_shell.p_cnt)
	{
		pid = fork();
		if (pid == 0)
		{
			get_output();
			command_select();
			exit(0);
		}
		else
		{
			if (g_shell.p != 0)
				close(g_shell.mpipe[g_shell.p - 1][0]);
			if (g_shell.p != g_shell.p_cnt)
				close(g_shell.mpipe[g_shell.p][1]);
			waitpid(pid, &g_shell.exit_status, 0);
			printf(".\t%d\t.\n",g_shell.exit_status);
		}
		g_shell.p++;
	}
}
