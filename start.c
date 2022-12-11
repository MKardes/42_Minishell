/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:04:25 by mkardes           #+#    #+#             */
/*   Updated: 2022/11/10 17:16:45 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_paths(char ***s)
{
	int		i;
	char	*tmp;
	char	*a;

	i = env_finder("PATH");
	tmp = ft_strchr(g_shell.env[i], '=');
	a = ft_strdup(tmp + 1);
	*s = ft_split(a, ':');
	free(a);
}

void	finder(void)
{
	int		i;
	char	*tmp;
	char	**s;

	get_paths(&s);
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
			break ;
		i++;
	}
	execve(g_shell.all[g_shell.p][0], g_shell.all[g_shell.p], g_shell.env);
	ft_error(g_shell.all[g_shell.p][0], "command not found");
	exit(127);
}

void	command_select2(int pid)
{
	if (g_shell.p_cnt == 0)
	{
		pid = fork();
		if (pid == 0)
			finder();
		else
			waitpid(pid, &g_shell.exit_status, 0);
		g_shell.exit_status /= 256;
	}
	else
		finder();
}

void	command_select(void)
{
	int	pid;

	pid = 0;
	redirections();
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
		command_select2(pid);
}

void	start(int pid)
{
	save_std_fds();
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
			g_shell.exit_status /= 256;
		}
		g_shell.p++;
	}
	restore_std_fds();
}
