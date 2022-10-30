/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 19:22:01 by mkardes           #+#    #+#             */
/*   Updated: 2022/10/12 13:03:52 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strstr(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i] == s2[i])
		return (1);
	return (0);
}
