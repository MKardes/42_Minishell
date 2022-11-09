/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 00:21:43 by mkardes           #+#    #+#             */
/*   Updated: 2022/11/09 20:41:15 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	partition(int p, int i, int j, int cnt)
{
	char	*s;
	int		a;
	int		z;
	int		tmp;

	g_shell.all[p] = (char **)malloc(sizeof(char *) * (cnt + 1));
	g_shell.all[p][cnt] = NULL;
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
			{/*
				if (s[i] == '<' || s[i] == '>')
				{
					i++;
					if (s[i] == '<' || s[i] == '>')
						i++;
					i++;
					break;
				}*/
				i++;
			}
		}
		z = i - z;
		if (g_shell.in_pipe[p] != a)
			g_shell.all[p][a] = ft_substr(s, i - z, z);
		a++;
	}
}

void	partition_func(char	*s, int *i, int tmp, int j)
{
	if (s[*i] == '\"')
	{
		while (s[++(*i)] != '\"' && (*i) - tmp < j)
			;
		(*i)++;
	}
	else if (s[(*i)] == '\'')
	{
		while (s[(++(*i))] != '\'' && (*i) - tmp < j)
			;
		(*i)++;
	}
}
//This function allocates to the string parts and fill them into the correct parts.

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
			break;
		cnt++;
		while (a < j && s[i + a] != 32)
		{
			if (s[i + a] == '\"' || s[i + a] == '\'')
				check_func(s, i, &a, j);
			else
			{
				/*
				if (ft_strchr("<>", s[i + a]))
				{
					cnt++;
					if (s[i + a + 1] == '<' || s[i + a + 1] == '>')
					{
						if (!s[i + a + 2])
							cnt--;
						a++;
					}
					else if (!s[i + a + 1])
						cnt--;
					a++;
					break;
				}*/
				a++;
			}
		}
		if (a >= j)
			break;
	}
	printf("cnt: %d\n",cnt);
	g_shell.in_pipe[p] = cnt;
	if (p == g_shell.p_cnt)
		g_shell.in_pipe[p] = cnt;
	partition(p, i, j, cnt);
}

void	check_func(char *s, int i, int *a, int j)
{
	if (s[i + (*a)] == '\"')
	{
		(*a)++;
		while (s[i + (*a)] != '\"' && (*a) < j)
			(*a)++;
		(*a)++;
	}
	else
	{
		(*a)++;
		while (s[i + (*a)] != '\'' && (*a) < j)
			(*a)++;
		(*a)++;
	}
}

void	quotes_state(char *s, int i, int *j, char c)//	This function passes the string until reach to the another \" or '
{
	(*j)++;//							To pass to the next character to continue the loop until reach the other \" or \'
	while (s[i + (*j)] != c && s[i + (*j)])
		(*j)++;
}

void	split_pipe(char *s)//					This function splits the string into the piped parts
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
			break;
		if (s[i + j] == '|' && !s[i + j + 1])//				"ls |" to not seg fault with that
			g_shell.all[p] = command__chc(p);
		i += j + 1;
		j = 0;
	}
}

void	pass(char *s, int *i, char c)
{
	(*i)++;
	while (s[*i] && s[*i] != c)
		(*i)++;
	(*i)++;
}

char	*add_space(char *s)
{
	char	*res;
	int	i;
	int	a;
	
	res = (char *)ft_calloc(ft_strlen(s) * 2, 1);
	i = 0;
	a = 0;
	while (s[i])
	{
		if (s[i] == '<' || s[i] == '>')
		{
			if (s[i + 1] == '<' || s[i + 1] == '>')
			{
				res[i + a] = ' ';
				a++;
				res[i + a] = s[i];
				i++;
				res[i + a] = s[i];
				i++;
				res[i + a] = ' ';
				a++;
			}
			else
			{
				res[i + a] = ' ';
				a++;
				res[i + a] = s[i];
				i++;
				res[i + a] = ' ';
				a++;
			}

		}
		res[i + a] = s[i];
		i++;
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
	g_shell.redirectors = (char **)ft_calloc(sizeof(char *), (g_shell.p_cnt + 1));
	g_shell.red_type = (char *)ft_calloc(1, (g_shell.p_cnt + 2));
	split_pipe(s);
	check_quote_var();
	printer();
	//redirections();
}
