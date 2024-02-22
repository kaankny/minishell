NAME = minishell
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
LIBS = -lreadline
# Path: src
SRCS = src/minishell.c \
		src/lexer/lexer.c src/lexer/lexer_text.c src/lexer/lexer_get_token.c src/lexer/lexer_utils.c \
		src/utils/utils.c src/utils/error.c src/utils/free.c src/utils/utils_extra.c \
		src/signal/signals.c \
		src/parser/parser.c src/parser/parser_utils.c src/parser/parser_get_cmd.c \
		src/parser/parser_add_content.c src/parser/parser_add_file.c src/parser/parser_add_flag.c \
		src/env/env.c src/env/env_utils.c src/env/env_utils_extra.c src/env/env_utils_pro.c \
		src/expander/expander.c src/expander/append.c \
		src/exc/execute.c \
		src/exc/execute_builtin.c src/exc/execute_utils.c src/exc/execute_utils2.c \
		src/exc/heredoc.c src/exc/multi_command.c src/exc/execute_execv.c \
		src/pathfinder/pathfinder.c \
		src/builtins/ft_echo.c src/builtins/ft_cd.c src/builtins/ft_pwd.c \
		src/builtins/ft_export.c src/builtins/ft_unset.c src/builtins/ft_env.c \
		src/builtins/ft_exit.c src/builtins/ft_export_utils.c src/utils/utils_command.c

# Path: libft
LIBFT = libft/libft.a

# Path: objs
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)
	@echo "\033[0;32mMinishell created\033[0;38m...\033[0m"

$(OBJ_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[0;38mCompiling \033[0;37m$<\033[0;38m...\033[0m"

clean:
	@make clean -C libft
	@rm -f $(OBJS)
	@echo "\033[0;38mCleaning \033[0;37m$(NAME)\033[0;38m...\033[0m"

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)
	@echo "\033[0;38mDeleting \033[0;37m$(NAME)\033[0;38m...\033[0m"

leaks:
	@make all
	@rm -f leaks.txt
	@echo "\033[0;38mRunning \033[0;37m$(NAME)\033[0;38m with valgrind...\033[0m"
	@valgrind --leak-check=full --show-leak-kinds=all --log-file=leaks.txt ./$(NAME)

re: fclean all

.PHONY: all clean fclean re leaks
