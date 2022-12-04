/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:49:10 by mkardes           #+#    #+#             */
/*   Updated: 2022/11/10 17:45:46 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*complete(char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i] != '$' && str[i])
		i++;
	res = malloc(i + 1);
	printf("r%p",res);
	i = 0;
	while (str[i] != '$' && str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*get_varriable(char *str)
{
	char	*res;
	char	*tmp;
	char	*res1;
	int		i;

	i = 0;
	res1 = ft_calloc(1, 1);
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			tmp = fill_it(&str[i]);
			while (str[i] != '$' && str[i] != ' ' && str[i])
				i++;
		}
		else
		{
			tmp = complete(&str[i]);
			while (str[i] != '$' && str[i])
				i++;
		}
		res = ft_strjoin(res1, tmp);
		free(res1);
		res1 = res;
		free(tmp);
	}
	return (res);
}

//parametre aldım
void	cpy_without_qoute(char *new, const char *src, char c, int i)
{
	while (src[i])
	{
		if (src[i] == '\"' || src[i] == '\'')
		{
			c = src[i];
			src++;
			while (src[i] != c && src[i])
			{
				new[i] = src[i];
				i++;
			}
			if (src[i])
				src++;
		}
		else
		{
			new[i] = src[i];
			i++;
		}
	}
}

char	*rm_quotes(char *str)
{
	char	*new;
	int		i;
	int		cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			quotes_state(str, 0, &i, str[i]);
			cnt += 2;
		}
		if (str[i])
			i++;
	}
	new = ft_calloc(ft_strlen(str) + 1 - cnt, sizeof (char));
	cpy_without_qoute(new, str, 0, 0);
	return (new);
}

void	check_quote_var(void)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i <= g_shell.p_cnt)
	{
		j = 1;
		while (j < g_shell.in_pipe[i])
		{
			tmp = rm_quotes(g_shell.all[i][j]);
			free(g_shell.all[i][j]);
			g_shell.all[i][j] = get_varriable(tmp);
			free(tmp);
			j++;
		}
		i++;
	}
}
