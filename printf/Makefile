NAME = libftprintf.a

SRCS = ft_putchar.c ft_printf.c ft_putstr.c ft_putnbr_base.c ft_putnbr.c

CC = cc

CFLAGS = -Wall -Werror -Wextra

OBJECT_FILES = $(patsubst %.c,%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJECT_FILES)
	ar -rcs $(NAME) $(OBJECT_FILES)

%.o: %.c printf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECT_FILES)

fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: clean