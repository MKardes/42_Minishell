/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 20:01:56 by mkardes           #+#    #+#             */
/*   Updated: 2022/10/12 13:02:05 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_fsplit(char *str, char c)
{
	int		i;
	char	*s;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	if (!str[i])
		return (NULL);
	s = malloc(i + 1);
	ft_strlcpy(s, str, i + 1);
	return (s);
}
