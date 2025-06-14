# Project
NAME = minishell

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -O0 -fsanitize=address

# Directories
SRCS_DIR = sources
OBJS_DIR = objects
LIBS_DIR = libraries
LIBFT_DIR = $(LIBS_DIR)/libft

INCLUDES = -I./includes -I$(LIBFT_DIR)

# Libs
LIBS = -L$(LIBFT_DIR) -lft -lreadline -lncurses

# Source files (explicitly listed)
SRCS = \
	$(SRCS_DIR)/main.c \
	$(SRCS_DIR)/ast_tree/ast_free_functions.c \
	$(SRCS_DIR)/ast_tree/node_ast_functions.c \
	$(SRCS_DIR)/built_in/cd.c \
	$(SRCS_DIR)/built_in/echo.c \
	$(SRCS_DIR)/built_in/env.c \
	$(SRCS_DIR)/built_in/exit.c \
	$(SRCS_DIR)/built_in/export.c \
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
	$(SRCS_DIR)/expansion/expansion.c \
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

# Object files (same structure in OBJS_DIR)
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# Build
all: $(LIBFT_DIR)/libft.a $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Libft
$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

# Clean
clean:
	@$(RM) -r $(OBJS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
