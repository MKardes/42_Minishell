/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:04:25 by mkardes           #+#    #+#             */
/*   Updated: 2022/10/19 11:00:40 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start1(void)
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
	//execve=
	//lstat
	//stat
	
	//cd
	//chdir				chdir		(const char *path)
	//DIR				*opendir	(const char *name)
	//struct dirent		*readdir	(DIR *drip)
	//int				closedir	(DIR *drip)
	//int				unlink		(const char *path)

	//denme();
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
