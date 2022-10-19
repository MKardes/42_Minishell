/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strddup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:08:02 by mkardes           #+#    #+#             */
/*   Updated: 2022/10/19 15:54:27 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	**ft_strddup(char **str)
{
	char	**s;
	int		i;

	i = 0;
	if (!str || !str[0])
		return (NULL);
	while (str[i])
		i++;
	s = (char **)malloc(sizeof(char *) * i + 1);
	s[i] = NULL;
	i--;
	while (i >= 0)
	{
		s[i] = ft_strdup(str[i]);
		i--;
	}
	return (s);
}
