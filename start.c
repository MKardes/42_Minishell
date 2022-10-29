/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:04:25 by mkardes           #+#    #+#             */
/*   Updated: 2022/10/26 19:41:53 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell g_shell;

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
	dup2(g_shell.pipes[g_shell.p % 2][1], 1);
	close(g_shell.pipes[g_shell.p % 2][1]);
	close(g_shell.pipes[g_shell.p % 2][1]);
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
	s = ft_split(a, ':');
	free(a);
	i = 0;
/*	if (g_shell.p != 0)
	{
		dup2(g_shell.pipes[g_shell.p - 1 % 2][0], 0);
		close(g_shell.pipes[g_shell.p - 1 % 2][0]);
		close(g_shell.pipes[g_shell.p - 1 % 2][1]);		
	}*/
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
	exit(0);
}

void	command_select(void)
{
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
		int	pid;

		pid = fork();
		if (pid == 0)
			finder();
		else
		{
			//close(g_shell.pipes[g_shell.p - 1 % 2][0]);
			wait(&pid);
		}
	}
}

void	start(void)
{
/*
	int	pid;

	while (g_shell.p != g_shell.p_cnt)
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
			{
				close(g_shell.pipes[g_shell.p - 1 % 2][0]);
				close(g_shell.pipes[g_shell.p - 1 % 2][1]);
			}
			wait(&pid);
		}
		g_shell.p++;
	}*/
	command_select();
}
