/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:49:10 by mkardes           #+#    #+#             */
/*   Updated: 2022/11/10 17:45:46 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cut_var(char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i] != '$' && str[i] != 96 && str[i] != ' ' && str[i])
		i++;
	res = malloc(i + 1);
	i = 0;
	while (str[i] != '$' && str[i] != 96 && str[i] != ' ' && str[i])
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
		if (str[0] == '?' && !str[1])
			return (ft_itoa(g_shell.exit_status));
		return (ft_strdup(""));
	}
	else
	{
		tmp = ft_strchr(g_shell.env[i], '=');
		res = ft_strdup(++tmp);
		return (res);
	}
}
