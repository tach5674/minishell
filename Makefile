# Project name
NAME = minishell

# Readline and libft
READLINE = readline
LIBFT = libft

# Compiler and flags
CC = cc
LIBS_DIR = libraries
READLINE_LIB_PATH = $(LIBS_DIR)/$(READLINE)/lib
CFLAGS = -Wall -Wextra -Werror -I./includes -I./$(LIBS_DIR)/$(READLINE)/include -I./$(LIBS_DIR)/$(LIBFT) #-fsanitize=address

# Directories
SRCS_DIR = sources
OBJS_DIR = objects

# Find all .c files and keep relative paths
SRCS = $(shell find $(SRCS_DIR) -name "*.c")
SRC_REL = $(subst $(SRCS_DIR)/,,$(SRCS))
OBJS_NAME = $(SRC_REL:.c=.o)
OBJS = $(addprefix $(OBJS_DIR)/, $(OBJS_NAME))

# Compilation targets
all: $(LIBS_DIR)/$(READLINE) $(LIBS_DIR)/$(LIBFT)/libft.a $(NAME)

# Main target
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ \
		-L$(READLINE_LIB_PATH) -lreadline \
		-L$(LIBS_DIR)/$(LIBFT) -lft \
		-lncurses

# Object rule with directory creation
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Build readline
$(LIBS_DIR)/$(READLINE):
	./$(LIBS_DIR)/readline_config $(READLINE)

# Build libft
$(LIBS_DIR)/$(LIBFT)/libft.a:
	$(MAKE) -C $(LIBS_DIR)/$(LIBFT)

# Clean
clean:
	@$(RM) $(OBJS)
	@$(MAKE) -C $(LIBS_DIR)/$(LIBFT) clean

fclean: clean
	@$(RM) $(NAME) linux_minishell
	@rm -rf $(LIBS_DIR)/$(READLINE)
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -C $(LIBS_DIR)/$(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re
