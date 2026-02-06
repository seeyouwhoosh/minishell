# Special targets
.POSIX:
.PHONY: clean re fclean all


# Color
BBLUE		= \033[1;34m
GREEN		= \033[0;32m
NC			= \033[0m

# Compiler
NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g
MAKE		= make -sC
RM			= rm -rf

# Libs
LINKER		= -lreadline
LIBFT_DIR	= include/libft
LIBFT		= $(LIBFT_DIR)/libft.a
LINKER		+= -lft -L$(LIBFT_DIR)

# Includes
INCLUDE_DIR	= include
INCLUDES	= -I$(INCLUDE_DIR) -I$(LIBFT_DIR)

# Sources
SRC_DIR		= src
SOURCES		= main.c utils.c utils2.c signal.c init.c frees.c \
	builtin/cd.c builtin/echo.c builtin/env_utils.c builtin/env_utils2.c builtin/env.c builtin/exit.c builtin/export.c builtin/pwd.c builtin/unset.c \
	execution/builtin.c execution/execute_main.c execution/execute_utils.c execution/execute_utils2.c execution/here_doc.c
# parsing/parse_main.c parsing/parse_utils.c parsing/parse_utils2.c parsing/parse_utils3.c parsing/parse.c parsing/var_expansion.c 

# Objects
OBJ_DIR		= obj
OBJ			= $(SOURCES:.c=.o)
OBJECTS		= $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))

# Bonus sources
BSRC_DIR	= src_bonus
BSOURCES	= 

# Bonus objects
BOBJ_DIR	= obj_bonus
BOBJECTS	= $(addprefix $(BOBJ_DIR)/, $(BSOURCES:.c=.o))

ifeq ($(uname), "Darwin")
	LINKER	+= -L/opt/homebrew/opt/readline/lib
	INCLUDES+= -I/opt/homebrew/opt/readline/include
endif

all: $(OBJECTS) $(NAME)


# Main program
all: $(LIBFT) $(OBJECTS) $(NAME)

$(LIBFT):
	make bonus -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJECTS)
	@echo "$(BBLUE)$(NAME)$(NC): Creating $(GREEN)$@$(NC)..."
	$(CC) $(CFLAGS) $(OBJECTS) $(LINKER) -o $@
	@echo "$(BBLUE)$(NAME)$(NC): $(GREEN)$(NAME)$(NC) created"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/builtin
	@mkdir -p $(OBJ_DIR)/execution
	@mkdir -p $(OBJ_DIR)/parsing
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 


# Bonus program
bonus: $(BOBJECTS)
	@echo "$(BBLUE)$(NAME)$(NC): Creating $(GREEN)$(NAME) ($@)$(NC)..."
	$(CC) $(CFLAGS) -o $(NAME) $(BOBJECTS) $(LINKER)
	@echo "$(BBLUE)$(NAME)$(NC): $(GREEN)$(NAME) ($@)$(NC) created"

$(BOBJ_DIR)/%.o: $(BOBJ_DIR)/%.c
	@mkdir -p $(BOBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


# Cleaning targets
clean:
	$(RM) $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean
	@$(RM) $(BOBJ_DIR)
	@echo "$(BBLUE)$(NAME)$(NC): Objects cleaned"

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean
	@echo "$(BBLUE)$(NAME)$(NC): Fully cleaned"

re: fclean all


