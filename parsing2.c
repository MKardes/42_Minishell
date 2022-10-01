/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:49:10 by mkardes           #+#    #+#             */
/*   Updated: 2022/10/01 18:26:56 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fill_it(char *str)
{
	int		i;
	char	*tmp;
	char	*res;

	if (!str)
		return (NULL);
	if (str[0] == '$')
	{
		i = env_finder(&str[1]);
		if (i == -1)
			return (NULL);
		else
		{
			tmp = ft_strchr(g_shell.env[i], '=');
			free(str);
			res = ft_strdup(++tmp);
			return (res);
		}
	}
	else
		return (str);
}

int	*f_space(char str)
{
	int	i;
	int	*ptr;
	int	len;
	int	idx;

	ptr = malloc(sizeof(int) * 100);
	idx = 0;
	len = 1;
	i = 0;
	while (str[i])
	{
		while (str[i] == ' ')
		{
			if (str[i + 1] == ' ')
			{
				ptr[idx] = len;
				len = 0;
				idx++;
			}
			i++;
			len++;
		}
		i++;
	}
}

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
		printf("[%s]\n", var[i]);
		tmp = fill_it(var[i]);
		if (tmp)
		{
			res = ft_strjoin(res, tmp);
			free(tmp);
		}
		i++;
	}
	char	*sss = ft_strdup("aaaaaaaaa");
	free(var);
	free(*str);
	*str = res;
}

void	var_chc(void)
{
	int	i;
	int	j;

	i = 0;
	while (i <= g_shell.p_cnt)
	{
		j = 1;
		while (j < g_shell.in_pipe[i])
		{
			get_var(&g_shell.all[i][j]);
			char	*op=ft_strdup("bbbbbbbb");
			j++;
		}
		i++;
	}
}
