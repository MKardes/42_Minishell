/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environmentals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:58:40 by mkardes           #+#    #+#             */
/*   Updated: 2022/10/07 21:19:17 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(void)
{
	int	i;

	i = 0;
	/*
	if (g_shell.in_pipe[g_shell.p] != 1)
	{
		ft_error("env", "Undifened option or argument");
		return ;
	}
	It's loced just to check environmental variables
	*/
	while (g_shell.env[i])
	{
		printf("%s\n", g_shell.env[i]);
		i++;
	}
}

// It checks if the environmental variable is exsits. Returns the index of it when it exists, if not it returns -1
int	check_if_exist(char **env, char *str)
{
	char	*s;
	char	*last;
	char	*var;
	char	*tmp;
	int		i;
	
	i = 0;
	s = ft_fsplit(str, '=');
	if (!s)
		return (0);
	last = ft_strdup(ft_strchr(str, '=') + 1);
	while (env[i])
	{
		var = ft_fsplit(env[i], '=');
		if (ft_strstr(var, s))
		{
			free(g_shell.env[i]);
			tmp = ft_strjoin(var, "=");
			g_shell.env[i] = ft_strjoin(tmp, last);
			free(tmp);
			free(s);
			free(var);
			free(last);
			return (1);
		}
		free(var);
		i++;
	}
	free(s);
	free(last);
	return (-1);
}

void	env_add(char *str)
{
	char	**n_env;
	int		i;
	int		j;

	i = 0;
	while (g_shell.env[i])
		i++;
	n_env = (char **)malloc(sizeof(char *) * (i + 1));
	j = -1;
	while (++j < i)
		n_env[j] = g_shell.env[j];
	n_env[i] = ft_strdup(str);
	i = -1;
	free(g_shell.env);
	g_shell.env = n_env;
	
}

void	my_export(void)
{
	int	i;

	i = 1;
	if (!operator_chc())
		return ;
	if (!g_shell.all[g_shell.p][1])
	{
		i = 0;
		while (g_shell.env[i])
		{
			printf("declare -x %s\n",g_shell.env[i]);
			i++;
		}
	}
	while (i < g_shell.in_pipe[g_shell.p])
	{
		int	h;
		h = check_if_exist(g_shell.env, g_shell.all[g_shell.p][i]);
		if (h == -1)
		{
			env_add(g_shell.all[g_shell.p][i]);
		}
		i++;
	}
}

void	sig_int(int sig)
{
	if (sig == SIGINT)
	{
		//rl_clear_history();
		//rl_on_new_line();
		//rl_redisplay();
		//rl_replace_line("aaaaaaa", 1);
		printf("\n%s", g_shell.prompt);
		free(g_shell.line);
		g_shell.line = NULL;
	}
}
