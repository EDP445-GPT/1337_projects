NAME		= philo

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
	CC       = cc

	CFLAGS   = -Wall -Wextra -Werror
else 
	CC       = cc
	CFLAGS   = -Wall -Wextra -Werror -g -pthread
endif

RM			= rm -f
HEADER		= ./header.h
LIBFT		= ./includes/libft/libft.a

SRCS		= main.c parsing.c

OBJ_SRCS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_SRCS) $(LIBFT) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ_SRCS) $(LIBFT) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C ./includes/libft

clean:
	@$(MAKE) clean -C ./includes/libft
	@$(RM) $(OBJ_SRCS)

fclean: clean
	@$(RM) $(LIBFT)
	$(RM) $(NAME)

re: fclean all

bc: all clean

.PHONY: all clean fclean re bc
