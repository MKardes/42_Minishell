#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <unistd.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct m_shell {
	char	**env;
	char	***all;
	char	**a;
	char	*line;
	char	*prompt;
	int		p_cnt;		//Pipe counts
	int		*in_pipe;	//The count of words in every pipes: in_pipe[0] = the word count in the first pipe
}	t_shell;

t_shell	shell_g;

#endif
