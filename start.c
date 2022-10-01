/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:04:25 by mkardes           #+#    #+#             */
/*   Updated: 2022/10/01 00:31:03 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	denme(void)
{
	int pid;
	int	mpipe[2];

	pipe(mpipe);
	pid = fork();	
	if (pid == 0)
	{
		dup2(mpipe[1], 1);
		printf ("Hello:)\n");
		exit(0);
	}
	wait(NULL);
	char	*buff = malloc(10);
	read(mpipe[0], buff, 999);
	printf("(%s)\n",buff);
	return (0);
}

void	start1(void)
{
	if (ft_strstr(shell_g.all[shell_g.p][0], "env"))
		env();
	else if (ft_strstr(shell_g.all[shell_g.p][0], "export"))
        my_export();
	else if (ft_strstr(shell_g.all[shell_g.p][0], "echo"))
		echo();
	else if (ft_strstr(shell_g.all[shell_g.p][0], "cd"))
		cd();
	else if (ft_strstr(shell_g.all[shell_g.p][0], "pwd"))
        pwd();
	else if (ft_strstr(shell_g.all[shell_g.p][0], "exit"))
		my_exit();
	else if (ft_strstr(shell_g.all[shell_g.p][0], "unset"))
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
	read(shell_g.mpipe[0], shell_g.info, 10000);
}

void	start(void)
{
	int	pid;

	if (shell_g.all[shell_g.p + 1] != NULL && shell_g.all[shell_g.p][0][0] == 'p')
    {
        pid = fork();
        if (pid == 0)
        {
            dup2(shell_g.mpipe[1], 1);
			close(shell_g.mpipe[0]);
			start1();
			close(shell_g.mpipe[1]);
			exit(0);
        }
		wait(NULL);
		info_();
		printf("(%s)\n", shell_g.info);
    }
	else
		start1();
}
