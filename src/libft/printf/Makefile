NAME        = libftprintf.a
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
AR          = ar rcs
RM          = rm -rf

# List your source files here
SRCS        = ft_printf.c \
              srcs/ft_print_char.c \
              srcs/ft_print_hex.c \
              srcs/ft_print_int.c \
              srcs/ft_print_pointer.c \
              srcs/ft_print_str.c \
              srcs/ft_print_unsigned_int.c \
              srcs/ft_strlen.c

# Automatically generate a list of object files from SRCS
OBJS        = $(SRCS:.c=.o)

###############################################################################
#                               RULES                                         #
###############################################################################

all: $(NAME)

# Compile each .c into a .o
# -I. ensures the compiler looks in the current directory for ft_printf.h
%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -I. -c $< -o $@

# Create the static library from all object files
$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

# Remove object files
clean:
	$(RM) $(OBJS)

# Remove object files and the library
fclean: clean
	$(RM) $(NAME)

# Rebuild everything from scratch
re: fclean all

.PHONY: all clean fclean re
