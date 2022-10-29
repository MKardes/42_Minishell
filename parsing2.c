/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:49:10 by mkardes           #+#    #+#             */
/*   Updated: 2022/10/22 20:52:32 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cut_var(char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i] != '$' && str[i] != ' ' && str[i])
		i++;
	res = malloc(i + 1);
	i = 0;
	while (str[i] != '$' && str[i] != ' ' && str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*fill_it(char *str)
{
	int		i;
	char	*tmp;
	char	*res;
	char	*var;

	if (!str)
		return (NULL);
	var = cut_var(str);
	i = env_finder(var);
	free(var);
	if (i == -1)
	{
		return (ft_strdup(""));
	}
	else
	{
		tmp = ft_strchr(g_shell.env[i], '=');
		res = ft_strdup(++tmp);
		return (res);
	}
}
/*
void	get_var(char **str)
{
	int		i;
	char	*res;
	char	*tmp;
	char	**var;
	int		*space;
	
	i = 0;
	res = ft_strdup("");
	space = f_space(*str);
	var = ft_dblsplit(*str, ' ', '$');
	while (var[i])
	{
		printf("aa[%s]\n", var[i]);
		tmp = fill_it(var[i]);
		if (tmp)
		{
			printf("a -[%s]",tmp);
			if (tmp[ft_strlen(tmp) - 1] == ' ')
				tmp = ft_spacejoin(tmp, space[i]);
			printf(" [%s]- b\n",tmp);
			res = ft_strjoin(res, tmp);
			printf("c\n");
			free(tmp);
		}
		i++;
	}
	free(var);
	free(*str);
	*str = res;
}*/

char	*complete(char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i] != '$' && str[i])
		i++;
	res = malloc(i + 1);
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
	int		a;

	i = 0;
	res1 = malloc(1);
	res1[0] = '\0';
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
		//printf("res-%p\nres1-%p\ntmp-%p\n\n",res,res1,tmp);
		free(res1);
		res1 = res;
		//printf("3-%p\n\n",res1);
		free(tmp);
	}
	return (res);
}

void	cpy_without_qoute(char **neww, const char *src)
{
	int		i;
	char	c;
	char	*new;

	new = *neww;
	i = 0;
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
	new[i] = '\0';
	*neww = new;
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
	new = malloc(ft_strlen(str) + 1 - cnt);
	cpy_without_qoute(&new, str);
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
			//printf("(%p)%s\n(%p)%s\n\n",g_shell.all[i][j], g_shell.all[i][j], tmp, tmp);
			free(g_shell.all[i][j]);
			g_shell.all[i][j] = get_varriable(tmp);
			free(tmp);
			j++;
		}
		i++;
	}
}
