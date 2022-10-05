/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 00:25:40 by mkardes           #+#    #+#             */
/*   Updated: 2022/10/01 00:40:10 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct m_shell {
	void	*funcs;
	char	**env;
	char	***all;
	char	*line;
	char	*prompt;
	int		p_cnt;		//Pipe counts   { echo "Mini" Shell | tr '\n' 'E' | cat > text.txt }  p_cnt = 2 
	int		*in_pipe;	//The count of words in every pipes: in_pipe[0] = the word count in the first pipe
	int		type;
	int		p;
	int		*mpipe;		//mpipe[0] read   --   mpipe[1] write
	char	*info;
}	t_shell;

t_shell	g_shell;

void	printer(void);
void	partition(int p, int i, int j, int c);
void	check_fill(char *s, int i, int j, int p);
void	quotes_state(int i, int *j, char c);
void	split_pipe(char *s);
void	pass(char *s, int *i, char c);
void	parsing(void);
void	myfree(void);
void	sig_int(int sig);
void	env(void);
void	my_export(void);
void	echo(void);
void	cd(void);
void	pwd(void);
void	start(void);
void	my_exit(void);
void	my_unset(void);
void	ft_error(char *command, char *msg);
int		operator_chc(void);
int		env_finder(char *str);
void	env_add(char *str);
void	var_chc(void);
void	check_func(char *s, int i, int *a, int j);
void	partition_func(char	*s, int *i, int tmp, int j);

#endif
