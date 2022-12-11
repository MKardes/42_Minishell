/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 00:25:40 by mkardes           #+#    #+#             */
/*   Updated: 2022/11/11 11:51:51 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	declare_env_add_check(char *s)
{
	int		e;
	int		d;
	char	*last;

	if (ft_strchr(s, '='))
		last = ft_strdup(ft_strchr(s, '=') + 1);
	else
		last = ft_strdup("");
	e = check_if_exist(g_shell.env, s, last);
	d = is_dec_exist(s, last);
	free(last);
	if (e == -1)
		env_add(s);
	if (d == -1)
		declare_add(s);
}

int	get_it(int i, char **last, char **var, char **s)
{
	char	*tmp;
	char	*tmp1;

	if (*last[0])
	{
		free(g_shell.declares[i]);
		tmp = ft_strjoin(*var, "=\"");
		tmp1 = ft_strjoin(*last, "\"");
		g_shell.declares[i] = ft_strjoin(tmp, tmp1);
		my_free_1(&tmp, s, &tmp1);
	}
	free(*var);
	return (1);
}

int	is_dec_exist(char *str, char *last)
{
	int		i;
	char	*var;
	char	*s;

	i = 0;
	s = ft_fsplit(str, '=');
	if (!s)
		s = ft_strdup(str);
	while (g_shell.declares && g_shell.declares[i])
	{
		var = ft_fsplit(g_shell.declares[i], '=');
		if (!var)
			var = ft_strdup(g_shell.declares[i]);
		if (ft_strstr(var, s))
			return (get_it(i, &last, &var, &s));
		free(var);
		i++;
	}
	return (my_free_2(&s));
}
