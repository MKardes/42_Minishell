NAME = minishell
NAME_W = minishell.exe
MLIB = libft/libft.a
LIBS = readline/lib
INCLUDES = readline/include
RL = -lreadline
GFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(MLIB) $(LIBS) *.c M_SRC/*.c
	@gcc *.c M_SRC/*.c $(MLIB) -L $(LIBS) -I $(INCLUDES) $(RL) -o $(NAME)
	@echo "Compiling Done"

win: $(NAME_W)

$(NAME_W): $(MLIB) $(LIBS) *.c W_SRC/*.c
	@gcc *.c W_SRC/*.c $(MLIB) $(RL) -o $(NAME_W)
	@echo "Compiling Done"

run: $(NAME)
	./$(NAME)
 
$(MLIB): libft
	@make -C libft

clean:
	make clean -C libft

fclean: clean
	make fclean -C libft
	rm -rf minishell

re: fclean all

.PHONY: re all fclean clean
