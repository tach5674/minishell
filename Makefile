# Project
NAME = minishell

# Authors
AUTHORS = ggevorgi & mzohraby

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

# Directories
SRCS_DIR = sources
OBJS_DIR = objects
LIBS_DIR = libraries
LIBFT_DIR = $(LIBS_DIR)/libft

INCLUDES = -I./includes -I$(LIBFT_DIR)

# Libs
LIBS = -L$(LIBFT_DIR) -lft -lreadline -lncurses

# Source files
SRCS = \
	$(SRCS_DIR)/main.c \
	$(SRCS_DIR)/ast_tree/ast_free_functions.c \
	$(SRCS_DIR)/ast_tree/node_ast_functions.c \
	$(SRCS_DIR)/built_in/cd.c \
	$(SRCS_DIR)/built_in/echo.c \
	$(SRCS_DIR)/built_in/env.c \
	$(SRCS_DIR)/built_in/exit.c \
	$(SRCS_DIR)/built_in/export.c \
	$(SRCS_DIR)/built_in/export_utils.c \
	$(SRCS_DIR)/built_in/pwd.c \
	$(SRCS_DIR)/built_in/unset.c \
	$(SRCS_DIR)/execution/built-in_execution.c \
	$(SRCS_DIR)/execution/command_execution.c \
	$(SRCS_DIR)/execution/execution.c \
	$(SRCS_DIR)/execution/execution_utils.c \
	$(SRCS_DIR)/execution/get_path.c \
	$(SRCS_DIR)/execution/redirections.c \
	$(SRCS_DIR)/execution/syntax_error_checker.c \
	$(SRCS_DIR)/expansion/argument_expansion.c \
	$(SRCS_DIR)/expansion/split_arguments.c \
	$(SRCS_DIR)/expansion/split_arguments_utils.c \
	$(SRCS_DIR)/expansion/expansion.c \
	$(SRCS_DIR)/expansion/expansion_utils.c \
	$(SRCS_DIR)/expansion/matches.c \
	$(SRCS_DIR)/expansion/process_matches.c \
	$(SRCS_DIR)/expansion/remove_quotes.c \
	$(SRCS_DIR)/expansion/tilde_expansion.c \
	$(SRCS_DIR)/expansion/wildcard_expansion.c \
	$(SRCS_DIR)/expansion/wildcard_utils.c \
	$(SRCS_DIR)/hash_table/ht_add.c \
	$(SRCS_DIR)/hash_table/ht.c \
	$(SRCS_DIR)/hash_table/ht_init.c \
	$(SRCS_DIR)/hash_table/ht_utils.c \
	$(SRCS_DIR)/parsing/heredoc.c \
	$(SRCS_DIR)/parsing/heredoc_utils.c \
	$(SRCS_DIR)/parsing/parse_cmd.c \
	$(SRCS_DIR)/parsing/parsing.c \
	$(SRCS_DIR)/shell/shell.c \
	$(SRCS_DIR)/signals/signals.c \
	$(SRCS_DIR)/tokenization/tokenizer.c \
	$(SRCS_DIR)/tokenization/utils.c \
	$(SRCS_DIR)/utils/error_utils.c \
	$(SRCS_DIR)/utils/utils1.c \
	$(SRCS_DIR)/utils/utils2.c \
	$(SRCS_DIR)/utils/sorting.c

# Object files
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# Colors
GREEN	= \033[38;2;109;173;126m
DARK_GREEN	= \033[38;2;63;166;90m
YELLOW	= \033[33m
RED		= \033[31m
RESET	= \033[0m
BLUE	= \033[34m
CYAN	= \033[36m
PURPLE	= \033[35m

# Build
all: lib $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBS)
	@printf "\n$(DARK_GREEN)"
	@printf "				$(DARK_GREEN)    ███▄ ▄███▓██▓███▄    █ ██▓ ██████ ██░ ██▓█████ ██▓    ██▓    $(GREEN)\n"
	@printf "				$(DARK_GREEN)   ▓██▒▀█▀ ██▓██▒██ ▀█   █▓██▒██    ▒▓██░ ██▓█   ▀▓██▒   ▓██▒    $(GREEN)\n"
	@printf "				$(DARK_GREEN)   ▓██    ▓██▒██▓██  ▀█ ██▒██░ ▓██▄  ▒██▀▀██▒███  ▒██░   ▒██░    $(GREEN)\n"
	@printf "				$(DARK_GREEN)   ▒██    ▒██░██▓██▒  ▐▌██░██░ ▒   ██░▓█ ░██▒▓█  ▄▒██░   ▒██░    $(GREEN)\n"
	@printf "				$(DARK_GREEN)   ▒██▒   ░██░██▒██░   ▓██░██▒██████▒░▓█▒░██░▒████░██████░██████▒$(GREEN)\n"
	@printf "\n"
	@printf "\n$(GREEN)🚀 Successfully built $(NAME) by $(AUTHORS)$(RESET)\n"
	@printf "$(YELLOW)💻 Type './minishell' to start your shell experience!$(RESET)\n\n"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@printf "$(PURPLE)🔧 Compiling: $(CYAN)%-50s$(PURPLE) ➜ $(GREEN)%s$(RESET)\n" "$<" "$@"

# Libft - silent build
lib:
	@make -s -C $(LIBFT_DIR)
	@printf "$(YELLOW)📚 Libft compiled successfully$(RESET)\n"

# Clean
clean:
	@rm -rf $(OBJS_DIR)
	@make -s -C $(LIBFT_DIR) clean
	@printf "$(RED)🧹 Cleaned up object files$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@make -s -C $(LIBFT_DIR) fclean
	@printf "$(RED)🔥 Full clean complete$(RESET)\n"

re: fclean all

.PHONY: all lib clean fclean re