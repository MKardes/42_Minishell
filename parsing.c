/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 00:21:43 by mkardes           #+#    #+#             */
/*   Updated: 2022/09/16 01:34:10 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	partition(int p, int i, int j, int c)
{
	char	*s;
	int		a;
	int		z;
	int		tmp;

	shell_g.all[p] = (char **)malloc(sizeof(char *) * c);
	s = shell_g.line;
	a = 0;
	tmp = i;
	while (i - tmp < j)
	{
		while (i - tmp < j && ((s[i] >= 9 && s[i] <= 13) || s[i] == 32))
			i++;
		z = i;
		if (s[i] == '\"')
		{
			while (s[++i] != '\"' && i - tmp < j)
				;
			i++;
		}
		else if (s[i] == '\'')
		{
			while (s[++i] != '\'' && i - tmp < j)
				;
			i++;
		}
		else
			while (i - tmp < j && !((s[i] >= 9 && s[i] <= 13) || s[i] == 32))
				i++;
		z = i - z;
		if (shell_g.in_pipe[p] != a)
			shell_g.all[p][a] = ft_substr(s, i - z, z);
		a++;
	}
}

//This function allocates to the string parts and fill them into the correct parts.
void	check_fill(char *s, int i, int j, int p)
{
	int	c;
	int	a;

	c = 0;
	a = 0;
	while (a < j)
	{
		while (a < j && ((s[i + a] >= 9 && s[i + a] <= 13) || s[i + a] == 32))
			a++;
		if (s[i + a] == '|' || !s[i + a])
			c--;
		c++;
		if (s[i + a] == '\"')
		{
			while (s[i + ++a] != '\"' && a < j)
				;
			a++;
		}
		else if (s[i + a] == '\'')
		{
			while (s[i + ++a] != '\'' && a < j)
				;
			a++;
		}
		else
			while (a < j && !((s[i + a] >= 9
						&& s[i + a] <= 13) || s[i + a] == 32))
				a++;
	}
	shell_g.in_pipe[p] = c;
	if (p == shell_g.p_cnt)
		shell_g.in_pipe[p] = c;
	partition(p, i, j, c);
}

void	quotes_state(int *a, int i, int *j, char c)//	This function passes the string until reach to the another \" or '
{
	char	*s;

	s = shell_g.line;
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
	shell_g.type = 1;
	while (s[i + j])
	{
		while (s[i + j] != '|' && s[i + j])
		{
			if (s[i + j] == '\"')
				quotes_state(0, i, &j, '\"');
			if (s[i + j] == '\'')
				quotes_state(0, i, &j, '\'');
			j++;
		}
		shell_g.type = 2;
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

void	parsing(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
			pass(s, &i, s[i]);
		if (s[i] == '|')
			shell_g.p_cnt++;
		i++;
	}
	shell_g.all = (char ***)malloc(sizeof(char **) * shell_g.p_cnt + 1);
	shell_g.in_pipe = (int *)malloc(sizeof(int) * shell_g.p_cnt + 1);
	split_pipe(s);
	printer();
}
