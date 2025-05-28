# Makefile for push_swap project

# Config
NAME        := push_swap
SRCDIR      := src
MAINDIR		:= $(SRCDIR)/push_swap
OPSDIR      := $(SRCDIR)/operations
OBJDIR      := obj
INCDIR      := includes
LIBFT_DIR   := libft

# Tools
CC          := cc
RM          := /bin/rm -f
MKDIR       := /bin/mkdir -p

# Flags
CFLAGS      := -Wall -Wextra -Werror
CPPFLAGS    := -I$(INCDIR) -I$(LIBFT_DIR)/includes -MD

# Linker flags
LDFLAGS     := -L$(LIBFT_DIR)
LDLIBS      := -lft

# Debugging support (optional)
ifeq ($(DEBUG), 1)
	CFLAGS += -g3 -O0
	LDFLAGS += -g3 -O0
endif

# Use vpath so make knows where to find the .c files
vpath %.c $(MAINDIR)
vpath %.c $(OPSDIR)

# Source files (no .c extensions)
SRC :=

# Files from push_swap/
SRC += push_swap
SRC += parse_args
SRC += validator
SRC += init_stack
SRC += index_utils
SRC += stack_utils
SRC += costs
SRC += targets
SRC += controller
SRC += controller_helpers



# # Source files (no .c extensions)
# SRC :=

# # Top-level src files
# SRC += push_swap
# SRC += parse
# SRC += stack_init
# SRC += error_handler
# SRC += stack_utils
# SRC += stack_a_utils
# SRC += stack_b_utils

# Files from operations/
SRC += push
SRC += reverse_rotate
SRC += rotate
SRC += swap
SRC += sort_three
# SRC += sort_controller

# Object files
OBJ := $(addprefix $(OBJDIR)/, $(SRC:=.o))
DEPS := $(OBJ:.o=.d)
-include $(DEPS)

# Default target
.DEFAULT_GOAL := all

# Build targets
all: $(LIBFT_DIR)/libft.a $(NAME)

$(NAME): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
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
