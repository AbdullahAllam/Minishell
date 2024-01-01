NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -I includes/ -I libft/includes/

LIBFT = -L libft -lft -lreadline -lhistory

HEADER = minishell.h

#BUILTINS = cd echo env exit export pwd unset
BUILTINS = ft_environment ft_pwd ft_exit ft_unset ft_echo cd export 


#ENV = environment obtain_env sort_env shell_level
ENV = environment obtain_env shell_level

#EXEC = bin builtin exec

#MAIN = minishell redir
MAIN = minishell


#PARSE = parse_line token_funcs expansions
PARSE = parse_line token_funcs

#ASSETS = fd_functions clean token kinds expansions parse_tools initiate
ASSETS = fd_functions clean token kinds parse_tools initiate extra_lines


#SRC = $(addsuffix .c, $(addprefix srcs/builtins/, $(BUILTINS))) \
	  $(addsuffix .c, $(addprefix srcs/environment/, $(ENV))) \
	  $(addsuffix .c, $(addprefix srcs/exec/, $(EXEC))) \
	  $(addsuffix .c, $(addprefix srcs/main/, $(MAIN))) \
	  $(addsuffix .c, $(addprefix srcs/parse/, $(PARSE))) \
	  $(addsuffix .c, $(addprefix srcs/assets/, $(ASSETS))) \

SRC = $(addsuffix .c, $(addprefix srcs/environment/, $(ENV))) \
	  $(addsuffix .c, $(addprefix srcs/main/, $(MAIN))) \
	  $(addsuffix .c, $(addprefix srcs/parse/, $(PARSE))) \
	  $(addsuffix .c, $(addprefix srcs/assets/, $(ASSETS))) \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n"
	@make -C libft/
	@echo "\033[0;32mCompiling minishell..."
	@$(CC) -o $(NAME) $(OBJ) $(LIBFT)
	@echo "\n\033[0mDone !"

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