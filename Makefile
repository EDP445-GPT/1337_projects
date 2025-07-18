NAME         = minishell

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
	CC       = cc

	CFLAGS   = -Wall -Wextra -Werror
	CPPFLAGS = -I/Users/mmaarafi/.brew/opt/readline/include
	LDFLAGS  = -L/Users/mmaarafi/.brew/opt/readline/lib -lreadline -lhistory
else 
	CC       = cc
	CFLAGS   = -Wall -Wextra -Werror -fsanitize=leak
	CPPFLAGS = -I/usr/include
	LDFLAGS  = -lreadline -lhistory
endif
# 

RM           = rm -f
HEADER       = ./includes/header.h
LIBFT        = ./includes/libft/libft.a

SRCS         = main.c tokenizer_one/custom_split.c  tokenizer_one/custom_split_utils.c tokenizer_one/tokenizer_one.c tokenizer_one/token_one_utils.c \
               tokenizer_one/token_two_utils.c utils/utils.c utils/linked_list_utils.c lexer/lexer.c parser/parser.c \
               expander/expander.c execution/execution.c execution/exec_utils.c builtins/export_not_real.c \
               builtins/cd.c lexer/update_env.c\
			         builtins/echo.c builtins/pwd.c builtins/exit.c builtins/unset.c builtins/env.c execution/redirect.c \
			         expander/ft_split_args_file.c  execution/herdoc.c  builtins/cd_utils.c\
     			 lexer/lexer_utils.c builtins/export_utils.c expander/split_args_utils.c \
				expander/expander_utils.c parser/parser_utils.c parser/parser_utils_second.c \
				 parser/parser_Redirs_utils.c parser/allocating_parser_utils.c expander/herdoc_expander_utils.c \
				 execution/exec_utils_second.c execution/exec_utils_third.c execution/exec_utils_forth.c \
				execution/herdoc_utils.c execution/exec_utils_fifth.c

OBJ_SRCS     = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_SRCS) $(LIBFT)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJ_SRCS) $(LIBFT) $(LDFLAGS) -o $(NAME)

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C ./includes/libft

clean:
	@$(MAKE) clean -C ./includes/libft
	@$(RM) $(OBJ_SRCS)

fclean: clean
	@$(MAKE) fclean -C ./includes/libft
	@$(RM) $(NAME)

re: fclean all

bc: all clean

.PHONY: all clean fclean re bc
