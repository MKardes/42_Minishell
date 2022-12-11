/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 01:24:24 by mkardes           #+#    #+#             */
/*   Updated: 2022/10/26 19:05:22 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_it_out(char **env, int j, int l)
{
	char	**new;
	int		i;

	i = 0;
	if (!env)
		return (NULL);
	if (l == 1)
	{
		free(env);
		return (NULL);
	}
	new = (char **)ft_calloc(l, sizeof(char *));
	while (i < j)
	{
		new[i] = env[i];
		i++;
	}
	free(env[i]);
	while (env[i + 1])
	{
		new[i] = env[i + 1];
		i++;
	}
	free(env);
	return (new);
}

void	remove_env_dec(char ***ptr, int i, int l)
{
	int		j;
	char	**str;
	char	*tmp;

	str = *ptr;
	j = 0;
	if (l == 0)
		return ;
	while (str && str[j])
	{
		tmp = ft_fsplit(str[j], '=');
		if (!tmp)
			tmp = ft_strdup(str[j]);
		if (ft_strstr(tmp, g_shell.all[g_shell.p][i]))
		{
			printf("Girdi\n");
			*ptr = get_it_out(str, j, l);
			free(tmp);
			break ;
		}
		free(tmp);
		j++;
	}
}

void	my_unset(void)
{
	int	env_len;
	int	dec_len;
	int	i;

	if (!g_shell.env || !operator_chc())
		return ;
	i = 1;
	while (i < g_shell.in_pipe[g_shell.p])
	{
		env_len = 0;
		dec_len = 0;
		if (!g_shell.env)
			break ;
		while (g_shell.env && g_shell.env[env_len])
			env_len++;
		while (g_shell.declares && g_shell.declares[dec_len])
			dec_len++;
		remove_env_dec(&g_shell.env, i, env_len);
		remove_env_dec(&g_shell.declares, i, dec_len);
		i++;
	}
	g_shell.exit_status = 0;
}
