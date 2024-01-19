NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -I includes/ -I libft/includes/

LIBFT = -L libft -lft -lreadline -lhistory

HEADER = minishell.h

BUILTINS = ft_environment ft_pwd ft_exit ft_unset ft_echo ft_cd ft_export 

ENV = environment obtain_env shell_level sorting_response

EXEC = binary built_ins execution

MAIN = minishell wiring

PARSE = parse_line token_funcs expand signals_handle

ASSETS = fd_functions clean token kinds parse_tools initiate extra_lines expand_funcs get_next_line get_next_line_utils


SRC = $(addsuffix .c, $(addprefix srcs/builtins/, $(BUILTINS))) \
	  $(addsuffix .c, $(addprefix srcs/environment/, $(ENV))) \
	  $(addsuffix .c, $(addprefix srcs/exec/, $(EXEC))) \
	  $(addsuffix .c, $(addprefix srcs/main/, $(MAIN))) \
	  $(addsuffix .c, $(addprefix srcs/parse/, $(PARSE))) \
	  $(addsuffix .c, $(addprefix srcs/assets/, $(ASSETS))) \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n"
	@make -C libft/
	@echo "\033[0;32mCompiling CATSHELL..."
	@$(CC) -o $(NAME) $(OBJ) $(LIBFT)
	@echo "\n\033[0mDone !"
	@echo "\t\t\t\t   /\\_/\\   "
	@echo "\t\t\t\t  ( o.o )  "
	@echo "\t\t\t\t   > ^ <   "
	@echo "\t\t\t\t CATSHELL   "

%.o: %.c
	@printf "\033[0;33mGenerating minishell objects... %-33.33s\r" $@
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "\033[0;31mCleaning libft..."
	@make clean -C libft/
	@echo "\nRemoving binaries..."
	@rm -f $(OBJ)
	@echo "\033[0m"

fclean:
	@echo "\033[0;31mCleaning libft..."
	@make fclean -C libft/
	@echo "\nDeleting objects and executable..."
	@rm -f $(OBJ) $(NAME)
	@echo "\033[0m"

re: fclean all

test: all
	./minishell

norm:
	norminette $(SRC) includes/$(HEADER)

.PHONY: clean fclean re test norm