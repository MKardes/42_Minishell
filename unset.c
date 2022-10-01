/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 01:24:24 by mkardes           #+#    #+#             */
/*   Updated: 2022/09/22 02:18:00 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_it_out(char **env, int j, int l)
{
	char	**new;
	int	i;

	i = 0;
	new = (char **)malloc(sizeof(char *) * l);
	while (i < j)
	{
		new[i] = env[i];
		i++;
	}
	free(env[i]);
	i++;
	while (i < l)
	{
		new[i - 1] = env[i];
		i++;
	}
	free(env);
	return (new);
}

void	my_unset(void)
{
	int		i;
	int		j;
	int		l;
	char	*tmp;

	if (!operator_chc())
		return ;
	i = 1;
	while (i < g_shell.in_pipe[g_shell.p])
	{
		l = 0;
		while (g_shell.env[l])
			l++;
		j = 0;
		while (g_shell.env[j])
		{
			tmp = ft_fsplit(g_shell.env[j], '=');
			if (ft_strstr(tmp, g_shell.all[g_shell.p][i]))
				g_shell.env = get_it_out(g_shell.env, j, l);
			free(tmp);
			j++;
		}
		i++;
	}
}
