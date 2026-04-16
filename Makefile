NAME            = minishell

LIBFT_DIR       = src/libft

LIBFT           = $(LIBFT_DIR)/libft.a
CC              = cc
CFLAGS          = -Wall -Wextra -Werror -g -I$(LIBFT_DIR)
LDFLAGS			= -lreadline

RM              = rm -rf
OBJ_DIR         = obj

SRCS            = src/minishell.c	src/utils/utils.c	src/env.c	src/prompt.c

OBJS            = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

GREEN           = \033[0;32m
RED             = \033[0;31m
RESET           = \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo -e "$(GREEN)Compiling $(NAME)...$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) all

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning objects..."
	$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "Cleaning executable..."
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

norm:
	@ERR_COUNT=$$(norminette src/ | grep "Error" | wc -l); \
	if [ $$ERR_COUNT -eq 0 ]; then \
		echo -e "$(GREEN)Norminette: TOUT EST PARFAIT !$(RESET)"; \
	else \
		echo -e "$(RED)Norminette: ERREURS TROUVÉES :$(RESET)"; \
		norminette src/ | grep "Error"; \
	fi

re: fclean all

.PHONY: all clean fclean re norm