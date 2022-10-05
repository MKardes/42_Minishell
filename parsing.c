/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 00:21:43 by mkardes           #+#    #+#             */
/*   Updated: 2022/10/05 18:09:22 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	partition(int p, int i, int j, int cnt)
{
	char	*s;
	int		a;
	int		z;
	int		tmp;

	g_shell.all[p] = (char **)malloc(sizeof(char *) * cnt);
	s = g_shell.line;
	a = 0;
	tmp = i;
	while (i - tmp < j)
	{
		while (i - tmp < j && s[i] == 32)
			i++;
		z = i;
		if ((s[i] == '\"') || (s[i] == '\''))
			partition_func(s, &i, tmp, j);
		else
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
		if (s[i + a] == '|' || s[i + a] == '\0')
		{
			cnt--;
			break;
		}
		cnt++;
		if ((s[i + a] == '\"' ) || (s[i + a] == '\''))
			check_func(s, i, &a, j);
		else 
			while (a < j && s[i + a] != 32)
			{
				if ((s[i + a] == '\"' ) || (s[i + a] == '\''))
					check_func(s, i, &a, j);
				else
					a++;
			}
	}
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

void	quotes_state(int i, int *j, char c)//	This function passes the string until reach to the another \" or '
{
	char	*s;

	s = g_shell.line;
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
				quotes_state(i, &j, '\"');
			if (s[i + j] == '\'')
				quotes_state(i, &j, '\'');
			j++;
		}
		check_fill(s, i, j, p);
		p++;
		if (!s[i + j])//						To break the loop when i + j + 1 not equal to '\0' character
			i--;
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

void	parsing(void)
{
	char	*s;
	int		i;

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
	printer();
	//var_chc();
}
