NAME        = minishell

CC          = cc
MAKEFLAGS += --no-print-directory
CFLAGS      = -Wall -Wextra -Werror -g
CPPFLAGS    = -I$(LIBFT_DIR)
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
    CFLAGS  += -I/opt/homebrew/opt/readline/include
    LDFLAGS += -L/opt/homebrew/opt/readline/lib -lreadline
else
    LDFLAGS += -lreadline
endif
OBJ_DIR     = obj
LIBFT_DIR   = src/libft
LIBFT       = $(LIBFT_DIR)/libft.a

SRCS        = \
	src/minishell.c \
	src/utils/utils.c \
	src/env.c \
	src/env_more.c \
	src/prompt.c \
	src/token_split.c \
	src/token.c \
	src/args.c \
	src/variable_extend.c \
	src/variable_extend_more.c \
	src/utils/parse_files.c \
	src/utils/parse_cmd.c \
	src/utils/free.c \
	src/open_file.c \
	src/utils/parse_cmd_more.c \
	src/utils/utils_files.c \
	src/utils/builtin.c \
	src/utils/builtin_more.c \
	src/executeur.c \
	src/executeur_setup.c \
	src/executeur_helpers.c \
	src/executeur_pipes.c \
	src/executeur_child.c \
	src/heredoc.c \
	src/utils/parse_cmd_more_more.c \
	src/utils/cd.c \
	src/utils/str_utils.c \

OBJS        = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

vpath %.c $(sort $(dir $(SRCS)))

RM          = rm -f
MKDIR       = mkdir -p

YELLOW      = \033[1;33m
CYAN        = \033[1;36m
BLUE        = \033[1;34m
RED         = \033[1;31m
RESET       = \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@printf "$(YELLOW)✔ $(NAME) built successfully$(RESET)\n"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) all

$(OBJ_DIR)/%.o: %.c
	@$(MKDIR) $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@printf "$(CYAN)• Compiled:$(RESET) %s\n" "$<"

clean:
	@$(RM) -r $(OBJ_DIR)
	@printf "$(BLUE)✦ Object files removed$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean:
	@$(RM) $(NAME)
	@printf "$(RED)✦ Executable removed$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) -r $(OBJ_DIR)
	@printf "$(BLUE)✦ Object files removed$(RESET)\n"

norm:
	@ERR_COUNT=$$(norminette src/ | grep "Error" | wc -l); \
	if [ $$ERR_COUNT -eq 0 ]; then \
		printf "$(YELLOW)Norminette: TOUT EST PARFAIT !$(RESET)\n"; \
	else \
		printf "$(RED)Norminette: ERREURS TROUVÉES :$(RESET)\n"; \
		norminette src/ | grep "Error"; \
	fi

re: fclean all

.PHONY: all clean fclean re norm