/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:49:10 by mkardes           #+#    #+#             */
/*   Updated: 2022/09/28 17:51:45 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_var1(char **var, *str)
{
	char	*res;
	char	*tmp;
	int		i;

	i = 0;
	while (var[i])
	{
		tmp = ft_strchr(var[i], '$');
		if (!tmp)
			res = ft_strjoin(res, var[i]);
		else
		{
			
			res = ft_strjoin(res, str);
		}
		i++;
	}
}

void	get_var(char **str)
{
	int		i;
	char	*res;
	int		j;
	char	**var;
	
	i = 0;
	var = ft_split(*str, ' ');
	get_var1(var, *str);
	while (str[0][i] && str[0][i] != '$')
		i++;
	if (str[0][i] != 0)
	{
		res = malloc(sizeof(char) * i + 1);
		ft_strlcpy(res, *str, i + 1);
	}
	j = i;
	while (str[0][i] && (str[0][i] != ' '))

}

void	var_chc(void)
{
	int	i;
	int	j;

	i = 0;
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
