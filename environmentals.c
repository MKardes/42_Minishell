/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environmentals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:58:40 by mkardes           #+#    #+#             */
/*   Updated: 2022/09/23 14:45:33 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(void)
{
	int	i;

	i = 0;
	/*
	if (shell_g.in_pipe[shell_g.p] != 1)
	{
		ft_error("env", "Undifened option or argument");
		return ;
	}
	It's loced just to check environmental variables
	*/
	while (shell_g.env[i])
	{
		printf("%s\n", shell_g.env[i]);
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
	last = ft_strchr(str, '=');
	last++;
	while (env[i])
	{
		var = ft_fsplit(env[i], '=');
		if (ft_strstr(var, s))
		{
			free(shell_g.env[i]);
			tmp = ft_strjoin(var, "=");
			shell_g.env[i] = ft_strjoin(tmp, last);
			free(tmp);
			free(s);
			return (1);
		}
		free(var);
		i++;
	}
	free(s);
	return (-1);
}

void	env_add(char *str)
{
	char	**n_env;
	int		i;
	int		j;

	i = 0;
	while (shell_g.env[i])
		i++;
	n_env = (char **)malloc(sizeof(char *) * (i + 1));
	j = -1;
	while (++j < i)
		n_env[j] = shell_g.env[j];
	n_env[i] = ft_strdup(str);
	i = -1;
	free(shell_g.env);
	shell_g.env = n_env;
}

void	my_export(void)
{
	int	i;

	i = 1;
	if (!operator_chc())
		return ;
	if (!shell_g.all[shell_g.p][1])
	{
		i = 0;
		while (shell_g.env[i])
		{
			printf("declare -x %s\n",shell_g.env[i]);
			i++;
		}
	}
	while (i < shell_g.in_pipe[shell_g.p])
	{
		int h = check_if_exist(shell_g.env, shell_g.all[shell_g.p][i]);
		if (h == -1)
		{
			env_add(shell_g.all[shell_g.p][i]);
			env();
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
		printf("\n%s", shell_g.prompt);
	}
}
