#include "minishell.h"

void    declare_sort();
char    *declare_add_quotes(char *s);

void	my_declares()
{
	int	i;

	i = 0;
	while (g_shell.declares[i])
	{
		printf("declare -x %s\n", g_shell.declares[i]);
		i++;
	}
}

void	declare_sort()
{
	int	len;
	int	i;
	int	j;
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
			if (ft_strncmp(g_shell.declares[j], g_shell.declares[j + 1], 1000) > 0)
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

char	*declare_add_quotes(char *s)
{
	char	*tmp;
	int	i;

	if (ft_strchr(s, '=') == 0)
		return (s);
	tmp = ft_calloc(ft_strlen(s) + 3, 1);
	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			break;
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

int	is_exist(char *str)
{
	int	i;
	char	*var;

	i = 0;
	while (g_shell.declares && g_shell.declares[i])
	{
		var = ft_fsplit(g_shell.declares[i], '=');
		if (ft_strstr(var, str))
		{
			free(var);
			return (1);
		}
		free(var);
		i++;
	}
	return (0);
}

void	declare_add(char *s)
{
	char	**n_dec;
	char	*str;
	int	i;
	int	j;

	i = 0;
	if (is_exist(s))
		return ;
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

void	declare_init(void)
{
	int	i;

	i = 0;
	while (g_shell.env[i])
	{
		declare_add(g_shell.env[i]);
		i++;
	}
	declare_sort();
}
