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
	int		len;
	int		i;
	int		a;
	char	*tmp;

	tmp = ft_calloc(256, 1);
	len = 0;
	a = 0;
	i = 0;
	while (s[i])
	{
		if (ft_strstr(s[i], ">") || (ft_strstr(s[i], ">>")
				||ft_strstr(s[i], "<") || ft_strstr(s[i], "<<")))
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

char	**cut_redirects(char **s, int i, int a)
{
	char	**res;
	char	*tmp;
	int		len;

	i = 1;
	a = 0;
	len = new_len(&tmp, s);
	res = (char **)ft_calloc(sizeof(char *), len + 1);
	if (!ft_strstr(s[0], ">") && !ft_strstr(s[0], ">>")
		&& !ft_strstr(s[0], "<") && !ft_strstr(s[0], "<<"))
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
	g_shell.in_pipe[g_shell.p] = len;
	free(s);
	free(tmp);
	return (res);
}

void	redirections(void)
{
	int		i;
	char	**s;

	s = g_shell.all[g_shell.p];
	i = 0;
	while (i < g_shell.in_pipe[g_shell.p])
	{
		if (ft_strstr(s[i], ">") || ft_strstr(s[i], ">>")
			|| ft_strstr(s[i], "<") || ft_strstr(s[i], "<<"))
			execute_redirect(s[i + 1], s[i]);
		i++;
	}
	g_shell.all[g_shell.p] = cut_redirects(s, 1, 0);
}
