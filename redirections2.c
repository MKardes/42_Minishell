/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:54:01 by mkardes           #+#    #+#             */
/*   Updated: 2022/11/11 11:53:07 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_std_fds(void)
{
	g_shell.save_fd[0] = dup(STDIN_FILENO);
	g_shell.save_fd[1] = dup(STDOUT_FILENO);
}

void	restore_std_fds(void)
{
	dup2(g_shell.save_fd[0], STDIN_FILENO);
	close(g_shell.save_fd[0]);
	dup2(g_shell.save_fd[1], STDOUT_FILENO);
	close(g_shell.save_fd[1]);
}

void	writable(char *file_name, int flag)
{
	int	fd;

	fd = open(file_name, flag, 0777);
	if (fd == -1)
	{
		ft_putendl_fd("not open fd", 2);
		return ;
	}
	dup2(fd, 1);
	close(fd);
}

void	readable(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY | O_CREAT, 0777);
	if (fd == -1)
	{
		ft_putendl_fd("not open fd", 2);
		return ;
	}
	dup2(fd, 0);
	close(fd);
}
