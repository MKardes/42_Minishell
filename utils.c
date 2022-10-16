/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:20:25 by mkardes           #+#    #+#             */
/*   Updated: 2022/10/12 12:55:18 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_finder(char *str)
{
	int		i;
	char	*var;

	i = 0;
	while (g_shell.env[i])
	{
		var = ft_fsplit(g_shell.env[i], '=');
		if (ft_strstr(var, str))
		{
			free(var);
			return (i);
		}
		free(var);
		i++;
	}
	return (-1);
}
