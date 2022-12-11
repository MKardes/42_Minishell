/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declare2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 00:25:40 by mkardes           #+#    #+#             */
/*   Updated: 2022/11/11 11:51:51 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*declare_add_quotes(char *s)
{
	char	*tmp;
	int		i;

	if (ft_strchr(s, '=') == 0)
		return (s);
	tmp = ft_calloc(ft_strlen(s) + 3, 1);
	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			break ;
		tmp[i] = s[i];
		i++;
	}
	tmp[i++] = '=';
	*(i + tmp++) = '\"';
	while (s[i])
	{
		tmp[i] = s[i];
		i++;
	}
	*(i + tmp++) = '\"';
	tmp[i] = '\0';
	free(s);
	return (tmp - 2);
}

void	declare_add(char *s)
{
	char	**n_dec;
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (g_shell.declares && g_shell.declares[i])
		i++;
	n_dec = (char **)ft_calloc(sizeof(char *), (i + 2));
	j = -1;
	while (++j < i)
		n_dec[j] = g_shell.declares[j];
	str = ft_strdup(s);
	n_dec[i] = declare_add_quotes(str);
	if (g_shell.declares)
		free(g_shell.declares);
	g_shell.declares = n_dec;
	declare_sort();
}

void	declare_sort(void)
{
	int		len;
	int		i;
	int		j;
	char	*tmp;

	len = 0;
	while (g_shell.declares[len])
		len++;
	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len - 1 - i)
		{
			if (ft_strncmp(g_shell.declares[j], g_shell.declares
					[j + 1], 1000) > 0)
			{
				tmp = g_shell.declares[j];
				g_shell.declares[j] = g_shell.declares[j + 1];
				g_shell.declares[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	declare_init(void)
{
	int	i;

	i = 0;
	while (g_shell.env[i])
	{
		declare_add(g_shell.env[i]);
		i++;
	}
}
