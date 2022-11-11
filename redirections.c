/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:54:01 by mkardes           #+#    #+#             */
/*   Updated: 2022/11/11 11:53:07 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_std_fds()
{
	g_shell.save_fd[0] = dup(STDIN_FILENO);
	g_shell.save_fd[1] = dup(STDOUT_FILENO);
}

void	restore_std_fds()
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

int	execute_redirect(char *file_name, char *str)
{
	if (ft_strstr(">", str))
		writable(file_name, O_WRONLY | O_CREAT | O_TRUNC);
	else if (ft_strstr("<", str))
		readable(file_name);
	else if (ft_strstr(">>", str))
		writable(file_name, O_WRONLY | O_CREAT | O_APPEND);
	else if (ft_strstr("<<", str))
	{
		heredoc();
		return (0);
	}
	return (1);
}

int	new_len(char **res, char **s)
{
	int	len;
	int	i;
	int	a;
	char	*tmp;

	tmp = ft_calloc(256, 1);
	len = 0;
	a = 0;
	i = 0;
	while (s[i])
	{
		if (ft_strstr(s[i], ">") || (ft_strstr(s[i], ">>") ||
			ft_strstr(s[i], "<") || ft_strstr(s[i], "<<")))
		{
			len--;
			tmp[a] = (char)i;
			tmp[a + 1] = (char)(i + 1);
			a += 2;
			i++;	
		}
		len++;
		i++;
	}
	*res = tmp;
	return (len);
}

char	**cut_redirects(char **s)
{
	char	**res;
	char	*tmp;
	int	len;
	int	i;
	int	a;

	len = new_len(&tmp, s);
	res = (char **)ft_calloc(sizeof(char *), len + 1);
	i = 1;
	a = 0;
	if (!ft_strstr(s[0], ">") && !ft_strstr(s[0], ">>") && !ft_strstr(s[0], "<") && !ft_strstr(s[0], "<<"))
		res[0] = s[0];
	while (i + a < g_shell.in_pipe[g_shell.p])
	{
		while (i + a < g_shell.in_pipe[g_shell.p] && ft_strchr(tmp, i + a))
		{
			free(s[i + a]);
			a++;
		}
		res[i] = s[i + a];
		i++;
	}
	//free(s[i + a]);
	g_shell.in_pipe[g_shell.p] = len;
	free(s);
	return (res);
}

void	redirections(void)
{
	int	i;
	char	**s;
	int	save_fd[2];

	s = g_shell.all[g_shell.p];
	i = 0;
	while (i < g_shell.in_pipe[g_shell.p])
	{
		if (ft_strstr(s[i], ">") || ft_strstr(s[i], ">>") ||
			ft_strstr(s[i], "<") ||ft_strstr(s[i], "<<"))
			execute_redirect(s[i + 1], s[i]);
		i++;
	}
	g_shell.all[g_shell.p] = cut_redirects(s);
}
