CC = cc
CFLAGS = -Wall -Wextra -Werror -I libft	#Compiler flags
LFLAGS = -lreadline -ltinfo				#Linker flags
NAME = minishell

OBJ_DIR = obj
SRC_MAIN = index.c utils.c \
			cmd_list/create_cmd_list.c cmd_list/assign_cmd.c \
			cmd_list/assign_input_file.c cmd_list/heredoc_expansion.c \
			cmd_list/assign_output_file.c \
			built_in/identify_commands.c built_in/ft_exit.c \
			built_in/ft_echo.c built_in/ft_pwd.c built_in/ft_env.c \
			built_in/ft_export.c built_in/ft_export_print.c \
			built_in/ft_export_append.c built_in/ft_unset.c \
			built_in/ft_cd.c built_in/ft_cd_update.c \
			tokenize/tokenize_utils.c tokenize/check_tokens.c\
			tokenize/check_vars_and_quotes/parse_and_expand.c \
			tokenize/check_vars_and_quotes/count_args.c \
			tokenize/check_vars_and_quotes/parse_input.c \
			tokenize/check_vars_and_quotes/variable_expansion.c \
			tokenize/tokenizer.c tokenize/tokenize_input.c \
			tokenize/tokenize_output.c tokenize/tokenize_words.c \
			cmd_execution/execute_cmd.c cmd_execution/execute_single_cmd.c \
			redirection/redirection_in.c redirection/redirection_out.c \
			pipes/pipe_check.c pipes/fd_matrix_utils.c pipes/init_firstcmd.c \
			pipes/middle_cmds.c pipes/init_lastcmd.c \
			free_memory/free_memory.c \
			signals/signals.c signals/sig_handle.c \
			print_banner.c \

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
CYAN = \033[36m

all: $(LIBFT) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/cmd_list $(OBJ_DIR)/built_in \
		$(OBJ_DIR)/tokenize $(OBJ_DIR)/tokenize/check_vars_and_quotes \
		$(OBJ_DIR)/cmd_execution $(OBJ_DIR)/redirection $(OBJ_DIR)/pipes \
		$(OBJ_DIR)/free_memory $(OBJ_DIR)/signals

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --quiet

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) -c $(CFLAGS) $< -g -o $@
	@echo "$(CYAN)Compiled $<$(NO_COLOR)"

$(NAME): $(OBJECTS) $(LIBFT)
	@$(CC) $(OBJECTS) $(LIBFT) $(LFLAGS) -o $(NAME)
	@echo "$(GREEN)Executable created!$(NO_COLOR)"

clean:
	@echo "$(YELLOW)Cleaning...$(NO_COLOR)"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --quiet

fclean: clean
	@echo "$(RED)Full Cleaning...$(NO_COLOR)"
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --quiet

re: fclean all

libft: $(LIBFT)

.PHONY: all clean fclean re libft
