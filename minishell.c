#include "minishell.h"

void	put_envs(void)
{
	int	i;

	i = 0;
	while (shell_g.env[i])
	{
		printf("%s\n", shell_g.env[i]);
		i++;
	}
}

void	partition(int p, int i, int j, int c)
{
	char	**pipe;
	char	*s;
	int		a;
	int		z;
	int		tmp;
	j--;
	pipe = (char **)malloc(sizeof(char *) * c);
	s = shell_g.line;
	a = 0;
	tmp = i;
	while (i - tmp < j)
	{
		while (i - tmp < j && ((s[i] >= 9 && s[i] <= 13) || s[i] == 32))
			i++;
		z = i;
		if (s[i] == '\"')
       	{
			while (s[++i] != '\"' &&  i - tmp < j);
			i++;
		}
		else if (s[i] == '\'')
		{
			while (s[++i] != '\'' &&  i - tmp < j);
			i++;
		}
		else
		{
			while (i - tmp < j && !((s[i] >= 9 && s[i] <= 13) || s[i] == 32))
				i++;
			printf("(%c)\n",s[i]);
		}
		z = i - z;
		if (s[i + 1] == '|')
		{
			printf("(%d/%c)%d--(%d/%c)%d, ",s[z], s[z], z,s[i], s[i], i);
			pipe[a] = ft_substr(s, i - z, z + 1);
		}
		else
            pipe[a] = ft_substr(s, i - z, z);
		a++;
	}
	shell_g.all[p] = pipe;
}

//This function allocates to the string parts and fill them into the correct parts.
void	check_fill(char *s, int i, int j, int p)
{
	int	c;
	int	a;

	c = 0;
	a = 0;
	while (a < j)
	{
		while (a < j && ((s[i + a] >= 9 && s[i + a] <= 13) || s[i + a] == 32))
			a++;
		if (s[i + a] == '|' || !s[i + a])
			c--;
		c++;
		if (s[i + a] == '\"')
		{
			while (s[i + ++a] != '\"' &&  a < j);
			a++;
		}
		else if (s[i + a] == '\'')
		{
			while (s[i + ++a] != '\'' &&  a < j);
			a++;
		}
		else
			while (a < j && !((s[i + a] >= 9 && s[i + a] <= 13) || s[i + a] == 32))
				a++;
	}
	shell_g.in_pipe[p] = c;
	if (p == shell_g.p_cnt)
		shell_g.in_pipe[p] = c;
	partition(p, i, j, c);
}

void	quotes_state(char *s, int i, int *j, char c)   //This function passes the string until reach to the another \" or '
{
	(*j)++;						  		//To pass to the next character to continue the loop until reach the other \" or \'
	while (s[i + (*j)] != c && s[i + (*j)])
		(*j)++;
}

void	split_pipe(char *s) 					//This function splits the string into the piped parts
{
	int	i;
	int	j;
	int	p;

	p = 0;
	i = 0;
	j = 0;
	while (s[i + j])
	{
		while (s[i + j] != '|' && s[i + j])
		{
			if (s[i + j] == '\"')
				quotes_state(s, i, &j, '\"');
			if (s[i + j] == '\'')
				quotes_state(s, i, &j, '\'');
			j++;
		}
		check_fill(s, i, j, p);
		p++;
		if (!s[i + j])							//To break the loop when i + j + 1 not equal to '\0' character
			i--;
		i += j + 1;
		j = 0;
	}
}

void	pass(char *s, int *i, char c)
{
	(*i)++;
	while (s[*i] && s[*i] != c)
		(*i)++;
	(*i)++;
}

void	parsing(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
			pass(s, &i, s[i]);
		if (s[i] == '|')
			shell_g.p_cnt++;
		i++;
	}
	shell_g.all = (char ***)malloc(sizeof(char **) * shell_g.p_cnt + 1);
	shell_g.in_pipe = (int *)malloc(sizeof(int) * shell_g.p_cnt + 1);
	i = 0;
	split_pipe(s);
	int	a = 0, b, c;
	printf("p_cnt: %d\n",shell_g.p_cnt);
	while (a <= shell_g.p_cnt)
	{
		printf("%d. word count: %d", a, shell_g.in_pipe[a]);
		b = 0;
		while (b < shell_g.in_pipe[a])
		{
			printf("[%s] ", shell_g.all[a][b]);
			b++;
		}
		a++;
		printf("\n");
	}
}

void	myfree(void)
{
	int	i;
	int	j;

	free(shell_g.line);
	i = 0;
	while (i< shell_g.p_cnt)
	{
		j = 0;
		while (j < shell_g.in_pipe[i])
		{
			free(shell_g.all[i][j]);
			j++;
		}
		i++;
	}
	free(shell_g.in_pipe);
	free(shell_g.all);
}

void	a(int sig)
{
	if (sig == SIGINT)
		printf("\n%s",shell_g.prompt);
}

int	main(int ac, char **av, char **env)
{
	char	*name;
	char	*s;

	if (ac != 1)
		return (0);
	shell_g.env = env;
	shell_g.p_cnt = 0;
	shell_g.prompt = ft_strdup("<\033[0;92m Shell\033[0;39m > ");
	signal(SIGINT, a);
	while(1)
	{
		shell_g.line = readline(shell_g.prompt);
		if (!shell_g.line)
		{
			printf("exit");
			exit(0);
		}
		add_history(shell_g.line);
		parsing(shell_g.line);
		shell_g.p_cnt = 0;
	//	myfree();
	}
	return (0);
}
