NAME = philo

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
	CC       = cc
	CFLAGS   = -Wall -Wextra -Werror #-fsanitize=threads
else 
	CC       = cc
	CFLAGS   = -Wall -Wextra -Werror -g -pthread -fsanitize=leak
endif

RM			= rm -f
HEADER		= ./header.h
SRCS		= main.c parsing.c atoi.c threads.c threads_utils.c

OBJ_SRCS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_SRCS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ_SRCS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ_SRCS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bc: all clean

.PHONY: all clean fclean re bc
