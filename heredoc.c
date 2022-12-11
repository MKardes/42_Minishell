/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:47:41 by mkardes           #+#    #+#             */
/*   Updated: 2022/11/11 11:52:40 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_doc(char *eof, char *doc_line)
{
	char	*heredoc_prompt;

	if (!eof)
		return (-1);
	if (eof[0] == '<')
	{
		ft_error("bash", "< usage error");
		return (-1);
	}
	heredoc_prompt = ft_strdup("heredoc> ");
	while (1)
	{
		doc_line = readline(heredoc_prompt);
		if (ft_strstr(eof, doc_line))
		{
			free(doc_line);
			break ;
		}
		write(g_shell.heredocpipe[1], doc_line, ft_strlen(doc_line));
		write(g_shell.heredocpipe[1], "\n", 1);
		free(doc_line);
	}
	close(g_shell.heredocpipe[1]);
	free(heredoc_prompt);
	return (0);
}

int	heredoc_fill(void)
{
	int	i;
	int	j;

	pipe(g_shell.heredocpipe);
	g_shell.p = 0;
	i = 0;
	while (i <= g_shell.p_cnt)
	{
		j = 0;
		while (j < g_shell.in_pipe[i])
		{
			if (ft_strstr("<<", g_shell.all[i][j]))
			{
				if (get_doc(g_shell.all[i][j + 1], NULL) == -1)
					return (-1);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	heredoc(void)
{
	dup2(g_shell.heredocpipe[0], 0);
	close(g_shell.heredocpipe[0]);
}
