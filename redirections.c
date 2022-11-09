/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:54:01 by mkardes           #+#    #+#             */
/*   Updated: 2022/11/09 17:39:42 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arg_count(char *s, int *chc, int cur)
{
	int	i;
	int	res;
	
	i = 0;
	res = 0;
	while (s[i])
	{
		if (*chc == 1 || *chc == 2)
		{
			if (g_shell.redirectors[cur])
			{
				free(g_shell.redirectors[cur]);
				g_shell.redirectors[cur] = NULL;
			}
			g_shell.red_type[cur] = *chc + 48;
			g_shell.redirectors[cur] = ft_fsplit(&s[i], '>');
			if (!g_shell.redirectors[cur])
				g_shell.redirectors[cur] = ft_fsplit(&s[i], '<');
			if (!g_shell.redirectors[cur])
				g_shell.redirectors[cur] = ft_strdup(&s[i]);
			*chc = 0;
		}
		if (s[i] == '<' || s[i] == '>')
		{
			if (s[i] == '>')
			{
				if (s[i + 1] == '>')
					*chc = 1;
				else
					*chc = 2;
			}
			if ((s[i] == '<' && s[i + 1] == '<')
				|| (s[i] == '>' && s[i + 1] == '>'))
			{
				i+=2;
				res -= 1;
			}
			else
			{
				i++;
				res -= 1;
			}
		}
		else
		{
			while(s[i] && s[i] != '>' && s[i] != '<')
				i++;
			res++;
		}
	}
	return res;
}

int	subtracted_cnt(int cur)
{
	int	i;
	int	res;
	int	chc;
	int	j;

	i = 0;
	res = 0;
	chc = 0;
	while (i < g_shell.in_pipe[cur])
	{
		res+=arg_count(g_shell.all[cur][i], &chc, cur);
		i++;
	}
	return res;
}

char	last_char(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i + 1] == '\0')
			return (s[i]);
		i++;
	}
	return (0);
}

char	**redirector_clear(int cur)
{
	int	i;
	int	cnt;
	int	chc;
	char	**tmp;
	char	*s;

	i = 0;
	chc = 0;
	cnt = subtracted_cnt(cur);
	tmp = malloc(sizeof(char *) * cnt);
	while (i < g_shell.in_pipe[cur])
	{
		s = g_shell.all[cur][i];
		if (s[i] != '<' || s[i] != '>')
		{
			if (chc == 0)
			{
				tmp[i] = ft_fsplit(s, '<');
				if (!tmp[i])
					tmp[i] = ft_fsplit(s, '>');
				if (!tmp[i])
					tmp[i] = ft_strdup(s);
			}
		}
		if (ft_strstr(s, "<") || ft_strstr(s, ">") || ft_strstr(s, "<<") || ft_strstr(s, ">>"))
			chc = 1;
		//if (last_char())
	}
	g_shell.in_pipe[cur] = cnt;
	return (tmp);
}

void	redirections(void)
{
	int	i;
	char	**tmp;

	i = 0;
	while (i <= g_shell.p_cnt)
	{
		tmp = redirector_clear(i);
//		free(g_shell.all[i]);
//		g_shell.all[i] = tmp;
		i++;
	}
}
