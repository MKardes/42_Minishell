/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:20:25 by mkardes           #+#    #+#             */
/*   Updated: 2022/09/23 14:05:33 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_finder(char *str)
{
	int		i;
	char	*var;

	i = 0;
	while (shell_g.env[i])
	{
		var = ft_fsplit(shell_g.env[i], '=');
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
