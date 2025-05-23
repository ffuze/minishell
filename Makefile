CC = cc
CFLAGS = -Wall -Wextra -Werror -lreadline -I libft -g
NAME = minishell

OBJ_DIR = obj
SRC_MAIN = index.c \
			utils.c \
			test_setup.c \
			built_in/ft_echo.c built_in/ft_pwd.c built_in/ft_env.c \
			built_in/ft_export.c built_in/ft_export_print.c \
			built_in/ft_export_append.c built_in/ft_cd.c built_in/ft_unset.c \
			tokenize/tokenizer.c tokenize/tokenize_input.c tokenize/tokenize_output.c\
			non_builtin/execute_cmd.c non_builtin/execute_single_cmd.c \
			redirection/redirection.c \
			pipes/pipe_check.c pipes/fd_matrix_utils.c pipes/firstandlast_cmds.c \
			pipes/middle_cmds.c\

OBJECTS_MAIN = $(SRC_MAIN:%.c=$(OBJ_DIR)/%.o)
OBJECTS_BONUS = $(SRC_BONUS:%.c=$(OBJ_DIR)/%.o)
OBJECTS = $(OBJECTS_MAIN)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
OTHER_DIRS = -lreadline -ltinfo

NO_COLOR = \033[0m
RED = \033[31m
GREEN = \033[32;5m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36;5m

all: $(LIBFT) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --quiet

$(NAME): $(LIBFT) $(SRC_MAIN)
	$(CC) $(CFLAGS) $(SRC_MAIN) $(LIBFT) $(OTHER_DIRS) -o $(NAME)
# togli OTHER_DIRS se da fastidio
	@echo "$(GREEN)Object files created!$(NO_COLOR)"

clean:
	@echo "$(YELLOW)Cleaning...$(NO_COLOR)"
	@	$(MAKE) -C $(LIBFT_DIR) clean --quiet

fclean: clean
	@echo "$(RED)Full Cleaning...$(NO_COLOR)"
	@	rm -rf $(OBJ_DIR) $(NAME)
	@	$(MAKE) -C $(LIBFT_DIR) fclean --quiet

re: fclean all

libft: $(LIBFT)

.PHONY: all clean fclean re libft
