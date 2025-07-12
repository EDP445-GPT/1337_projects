NAME = libft.a

SRCS = ft_isalnum.c ft_isprint.c ft_memcpy.c ft_putendl_fd.c ft_strchr.c ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c\
	ft_isalpha.c ft_itoa.c ft_memmove.c ft_putnbr_fd.c ft_strdup.c ft_strlcpy.c ft_strnstr.c ft_tolower.c\
	ft_bzero.c ft_isascii.c ft_memchr.c ft_memset.c ft_putstr_fd.c ft_striteri.c ft_strlen.c ft_strrchr.c ft_toupper.c\
	ft_calloc.c ft_isdigit.c ft_memcmp.c ft_putchar_fd.c ft_split.c ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_strcmp.c ft_strcat.c ft_strcpy.c

BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

CC = cc

CFLAGS = -Wall -Werror -Wextra

OBJECT_FILES = $(patsubst %.c,%.o,$(SRCS))

BONUS_OBJECT_FILES = $(patsubst %.c,%.o,$(BONUS))

all: $(NAME)

$(NAME): $(OBJECT_FILES)
	ar -rcs $(NAME) $(OBJECT_FILES)

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus: .bonus_f

.bonus_f: $(BONUS_OBJECT_FILES)
	ar -rcs $(NAME) $(BONUS_OBJECT_FILES)
	@touch .bonus_f

clean:
	rm -f $(OBJECT_FILES) $(BONUS_OBJECT_FILES) .bonus_f

fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: clean