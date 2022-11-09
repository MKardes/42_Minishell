/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 00:25:40 by mkardes           #+#    #+#             */
/*   Updated: 2022/11/08 20:37:38 by mkardes          ###   ########.fr       */
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
# include <sys/wait.h>
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
	int		**mpipe;	//*pipes[0] read   --   *pipes[1] write
	int		exit_status;
	char	*info;
	char	**redirectors;
	char	*red_type;
}	t_shell;

extern t_shell	g_shell;

void	printer(void);
void	partition(int p, int i, int j, int c);
void	check_fill(char *s, int i, int j, int p);
void	quotes_state(char *s, int i, int *j, char c);
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
int		command_chc(void);
char	**command__chc(int p);
void	env_add(char *str);
void	check_quote_var(void);
void	check_func(char *s, int i, int *a, int j);
void	partition_func(char	*s, int *i, int tmp, int j);
void	redirections(void);

#endif
