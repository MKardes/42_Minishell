NAME_W = minishell.exe
MLIB = libft/libft.a
RL = -lreadline
GFLAGS = -Wall -Werror -Wextra
SRCS = dir_cmnds.c echo.c environmentals.c free.c minishell.c parsing.c parsing2.c printer.c unset.c utils.c W_SRC/start.c

all: $(NAME_W)

run: $(NAME_W)
	./$(NAME_W)

$(NAME_W): $(MLIB) $(SRCS)
	@gcc $(SRCS) $(MLIB) $(RL) -o $(NAME_W)
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
