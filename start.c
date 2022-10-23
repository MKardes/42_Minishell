/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:04:25 by mkardes           #+#    #+#             */
/*   Updated: 2022/10/23 17:59:26 by ghaciosm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    path_finder(void)
{
    int     i;
    char    **s;
    char    *a;
    char    *c;
	char	*b;


    i = env_finder("PATH");
    a = ft_strchr(g_shell.env[i], '=');
    s = ft_split(a + 1, ':');
    i = 0;
    while(s[i])
    {
        c = ft_strjoin(s[i], "/");
		b = ft_strjoin(c, g_shell.all[g_shell.p][0]);
		free(c);
        if (execve(b, g_shell.all[g_shell.p], g_shell.env) != -1)
			break;
		free(b);
        i++;
    }
	exit(0);
}

void	start1(void)
{
	int	pid;

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
		pid = fork();
		if (pid == 0)
			path_finder();
		else
			wait(NULL);
	}
}

void	info_(void)
{
	read(g_shell.mpipe[0], g_shell.info, 10000);
}

void	start(void)
{
	int	pid;

	if (g_shell.all[g_shell.p + 1] != NULL && g_shell.all[g_shell.p][0][0] == 'p')
    {
        pid = fork();
        if (pid == 0)
        {
            dup2(g_shell.mpipe[1], 1);
			close(g_shell.mpipe[0]);
			start1();
			close(g_shell.mpipe[1]);
			exit(0);
        }
		wait(0);
		info_();
		printf("(%s)\n", g_shell.info);
    }
	else
		start1();
	
}
