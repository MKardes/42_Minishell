/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strddup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:08:02 by mkardes           #+#    #+#             */
/*   Updated: 2022/09/18 03:51:05 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	**ft_strddup(char **str)
{
	char	**s;
	int		i;

	i = 0;
	while (str[i])
		i++;
	s = (char **)malloc(sizeof(char *) * i);
	i--;
	while (i >= 0)
	{
		s[i] = ft_strdup(str[i]);
		i--;
	}
	return (s);
}
