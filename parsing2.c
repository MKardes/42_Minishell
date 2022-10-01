/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:49:10 by mkardes           #+#    #+#             */
/*   Updated: 2022/10/01 00:52:25 by mkardes          ###   ########.fr       */
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
			tmp = ft_strchr(shell_g.env[i], '=');
			res = ft_strdup(++tmp);
			return (res);
		}
	}
	else
		return (str);
}

void	get_var(char **str)
{
	int		i;
	char	*res;
	char	*tmp;
	char	**var;
	
	i = 0;
	res = ft_strdup("");
	var = ft_dblsplit(*str, ' ', '$');
	while (var[i])
	{
		tmp = fill_it(var[i]);
		if (tmp)
		{
			res = ft_strjoin(res, tmp);
			free(tmp);
		}
		i++;
	}
	printf("\\%s\n",res);
	free(var);
	*str = res;
}

void	var_chc(void)
{
	int	i;
	int	j;

	i = 0;
	printf("{%d, : %d, %d, %d}",shell_g.p_cnt, shell_g.in_pipe[0], shell_g.in_pipe[1], shell_g.in_pipe[2]);
	while (i <= shell_g.p_cnt)
	{
		j = 1;
		while (j < shell_g.in_pipe[i])
		{
			get_var(&shell_g.all[i][j]);
			j++;
		}
		i++;
	}
}
