/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 00:25:40 by mkardes           #+#    #+#             */
/*   Updated: 2022/11/11 11:51:51 by mkardes          ###   ########.fr       */
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

//p_cnt : Pipe counts
//in_pipe: The count of words in every pipes
//mpipe: *pipes[0] read   --   *pipes[1] write
//save_fd:
//heredoc_pipe:
typedef struct m_shell {
	void	*funcs;
	char	**env;
	char	**declares;
	char	***all;
	char	*line;
	char	*prompt;
	int		p_cnt;
	int		*in_pipe;
	int		type;
	int		p;
	int		**mpipe;
	int		exit_status;
	int		*save_fd;
	int		*heredocpipe;
}	t_shell;

t_shell	g_shell;

void	partition(int p, int i, int j, int c);
void	check_fill(char *s, int i, int j, int p);
void	quotes_state(char *s, int i, int *j, char c);
void	split_pipe(char *s, int i);
void	pass(char *s, int *i, char c);
void	parsing(void);
void	myfree(void);
void	sig_int(int sig);
void	env(void);
void	my_export(void);
void	echo(void);
void	cd(void);
void	pwd(void);
void	start(int pid);
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
void	save_std_fds(void);
void	restore_std_fds(void);
void	heredoc(void);
int		heredoc_fill(void);
void	partition_func(char	*s, int *i, int tmp, int j);
void	check_func(char *s, int i, int *a, int j);
void	quotes_state(char *s, int i, int *j, char c);
void	pass(char *s, int *i, char c);
char	*cut_var(char *str);
char	*fill_it(char *str);
char	*get_varriable(char *str);
void	save_std_fds(void);
void	restore_std_fds(void);
void	writable(char *file_name, int flag);
void	readable(char *file_name);
int		my_free_2(char **s);
void	my_free_1(char **tmp, char **s, char **var);
void	open_pipes(void);
char	**arg_add(char **arg, char *str);
void	get_output(void);
int		check_if_exist(char **env, char *str, char *last);

void	fix_var(char *s);
void	declare_add(char *str);
void	declare_init(void);
void	declare_sort(void);
void	declare_env_add_check(char *s);
int		is_dec_exist(char *str, char *last);
char	*declare_add_quotes(char *s);

#endif
