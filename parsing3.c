/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 00:21:43 by mkardes           #+#    #+#             */
/*   Updated: 2022/11/10 19:06:13 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// This function passes the string until reach to the another \" or '
void	quotes_state(char *s, int i, int *j, char c)
{
	(*j)++;
	while (s[i + (*j)] != c && s[i + (*j)])
		(*j)++;
}

void	pass(char *s, int *i, char c)
{
	(*i)++;
	while (s[*i] && s[*i] != c)
		(*i)++;
	(*i)++;
}
