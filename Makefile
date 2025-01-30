# Color variables
RESET = \033[0m
BOLD = \033[1m
GREEN = \033[32m
RED = \033[31m
YELLOW = \033[33m
CYAN = \033[36m

# Variables
LIBFT = libft
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -gdwarf-3
INCLUDES = includes/
IFLAGS = -I $(INCLUDES) 
SRC_DIR = src/
OBJ_DIR = objs
SRCS = $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)/%.o, $(SRCS))
NAME = minishell

# Rules
all: $(NAME)
	@echo "$(GREEN)Build completed$(RESET)"

$(NAME): $(OBJS)
	@echo "$(CYAN)Linking objects...$(RESET)"
	$(CC) $(CFLAGS) $(IFLAGS) -o $(NAME) $(OBJS) -L $(LIBFT) -lft -lreadline
	@echo "$(GREEN)Executable $(NAME) created$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	mkdir -p $(dir $@)
	make -C $(LIBFT)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@make clean -C $(LIBFT)
	rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(RED)Cleaning executable...$(RESET)"
	@make fclean -C $(LIBFT)
	rm -f $(NAME)

re: fclean all

v:					$(NAME)
					clear && valgrind --show-leak-kinds=all --leak-check=full --track-fds=all --track-origins=yes --suppressions=readline.supp ./minishell

.PHONY: all clean fclean re


