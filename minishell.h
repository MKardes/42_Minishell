/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 00:25:40 by mkardes           #+#    #+#             */
/*   Updated: 2022/09/16 15:09:57 by mkardes          ###   ########.fr       */
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
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct m_shell {
	char	**env;
	char	***all;
	char	*line;
	char	*prompt;
	int		p_cnt;		//Pipe counts
	int		*in_pipe;	//The count of words in every pipes: in_pipe[0] = the word count in the first pipe
	int		type;
	int		p;
}	t_shell;

t_shell	shell_g;

void	printer(void);
void	partition(int p, int i, int j, int c);
void	check_fill(char *s, int i, int j, int p);
void	quotes_state(int *a, int i, int *j, char c);
void	split_pipe(char *s);
void	pass(char *s, int *i, char c);
void	parsing(char *s);
void	myfree(void);
void	sig_int(int sig);
void	env(char *s);
void	start(void);

#endif
