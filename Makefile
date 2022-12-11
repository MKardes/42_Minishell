NAME = minishell
MLIB = libft/libft.a
RL = -lreadline
GFLAGS = -Wall -Werror -Wextra
SRCS = dir_cmnds.c echo.c environmentals.c environmentals2.c free.c minishell.c parsing.c parsing2.c parsing3.c parsing4.c unset.c utils.c start.c start2.c checks.c redirections.c redirections2.c heredoc.c declare.c declare2.c

all: $(NAME)

run: $(NAME)
	./$(NAME)

$(NAME): $(MLIB) $(SRCS)
	@gcc $(GFLAGS) $(SRCS) $(MLIB) $(RL) -o $(NAME)
	@echo "Compiling Done"
 
$(MLIB): libft
	@make -C libft

clean:
	make clean -C libft

fclean: clean
	make fclean -C libft
	rm -rf minishell.exe minishell

re: fclean all

.PHONY: re all fclean clean
