/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 00:21:43 by mkardes           #+#    #+#             */
/*   Updated: 2022/11/10 19:06:13 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	partition(int p, int i, int j, int cnt)
{
	char	*s;
	int		a;
	int		z;
	int		tmp;

	g_shell.all[p] = (char **)ft_calloc(sizeof(char *), (cnt + 1));
	s = g_shell.line;
	a = 0;
	tmp = i;
	while (i - tmp < j)
	{
		while (i - tmp < j && s[i] == 32)
			i++;
		z = i;
		while (i - tmp < j && s[i] != 32)
		{
			if ((s[i] == '\"') || (s[i] == '\''))
				partition_func(s, &i, tmp, j);
			else
				i++;
		}
		z = i - z;
		if (g_shell.in_pipe[p] != a)
			g_shell.all[p][a] = ft_substr(s, i - z, z);
		a++;
	}
}
//This function allocates to the string parts
//and fill them into the correct parts.

void	check_fill(char *s, int i, int j, int p)
{
	int	cnt;
	int	a;

	cnt = 0;
	a = 0;
	while (a < j)
	{
		while (a < j && s[i + a] == 32)
			a++;
		if (a == j)
			break ;
		cnt++;
		while (a < j && s[i + a] != 32)
		{
			if (s[i + a] == '\"' || s[i + a] == '\'')
				check_func(s, i, &a, j);
			else
				a++;
		}
		if (a >= j)
			break ;
	}
	g_shell.in_pipe[p] = cnt;
	partition(p, i, j, cnt);
}

//This function splits the string into the piped parts
void	split_pipe(char *s)
{
	int	i;
	int	j;
	int	p;

	p = 0;
	i = 0;
	j = 0;
	while (s[i + j])
	{
		while (s[i + j] != '|' && s[i + j])
		{
			if (s[i + j] == '\"')
				quotes_state(s, i, &j, '\"');
			if (s[i + j] == '\'')
				quotes_state(s, i, &j, '\'');
			j++;
		}
		check_fill(s, i, j, p);
		p++;
		if (!s[i + j])
			break ;
		if (s[i + j] == '|' && !s[i + j + 1])
			g_shell.all[p] = command__chc(p);
		i += j + 1;
		j = 0;
	}
}

char	*add_space(char *s)
{
	char	*res;
	int		i;
	int		a;

	res = (char *)ft_calloc(ft_strlen(s) * 2, 1);
	i = -1;
	a = 0;
	while (s[++i])
	{
		if (s[i] == '<' || s[i] == '>')
		{
			res[i + a++] = ' ';
			if (s[i + 1] == '<' || s[i + 1] == '>')
			{
				res[i + a] = s[i];
				i++;
			}
			res[i + a] = s[i];
			i++;
			res[i + a++] = ' ';
		}
		res[i + a] = s[i];
	}
	free(s);
	return (res);
}

void	parsing(void)
{
	char	*s;
	int		i;

	g_shell.line = add_space(g_shell.line);
	s = g_shell.line;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
			pass(s, &i, s[i]);
		if (s[i] == '|')
			g_shell.p_cnt++;
		i++;
	}
	g_shell.all = (char ***)malloc(sizeof(char **) * (g_shell.p_cnt + 1));
	g_shell.in_pipe = (int *)malloc(sizeof(int) * (g_shell.p_cnt + 1));
	split_pipe(s);
	check_quote_var();
}
