NAME = minishell
MLIB = libft/libft.a
LIBS = readline/lib
INCLUDES = readline/include
RL = -lreadline
GFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(MLIB) $(LIBS) *.c
	@gcc *.c $(MLIB) -L $(LIBS) -I $(INCLUDES) $(RL) -o $(NAME) -g
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
