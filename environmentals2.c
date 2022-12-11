/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environmentals2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:58:40 by mkardes           #+#    #+#             */
/*   Updated: 2022/10/24 20:41:00 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_free_2(char **s)
{
	free(*s);
	return (-1);
}

void	my_free_1(char **tmp, char **s, char **var)
{
	free(*tmp);
	free(*s);
	free(*var);
}
