# Makefile for push_swap project

# Config
NAME			:=	push_swap
SRCDIR			:=	src
OBJDIR			:=	obj
INCDIR			:=	includes
LIBFT_DIR		:=	libft

# Tools
CC				:=	cc
RM				:=	/bin/rm -f
MKDIR			:=	/bin/mkdir -p

# Flags
CFLAGS			:=	-Wall -Wextra -Werror
CPPFLAGS		:=	-I$(INCDIR) -I$(LIBFT_DIR)/includes -MD

# Linker flags
LDFLAGS			:=	-L$(LIBFT_DIR)
LDLIBS			:=	-lft

# Debugging support (optional)
ifeq ($(DEBUG), 1)
	CFLAGS += -g3 -O0
	LDFLAGS += -g3 -O0
endif

# Sources
SRC				:=	push_swap.c
OBJ				:=	$(SRC:.c=.o)
OBJ				:=	$(addprefix $(OBJDIR)/,$(OBJ))
DEPS			:=	$(OBJ:.o=.d)
-include $(DEPS)

# Default target
.DEFAULT_GOAL	:=	all

# Build target
all: $(LIBFT_DIR)/libft.a $(NAME)

$(NAME): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	$(MKDIR) $@

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

# Cleaning
clean:
	$(RM) $(OBJ) $(DEPS)
	$(RM) -r $(OBJDIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

run: all
	@echo "Running push_swap with ARGS='4 3 2 1'"
	@./$(NAME) $(ARGS)

.PHONY: all clean fclean re run
.SECONDARY:
.DELETE_ON_ERROR:
