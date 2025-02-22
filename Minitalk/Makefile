# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/12 18:34:59 by yazan             #+#    #+#              #
#    Updated: 2025/02/02 15:37:10 by mmaarafi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME_CLIENT = client
NAME_SERVER = server

SRC_CLIENT = client.c ft_atoi.c
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

SRC_SERVER = server.c ft_itoa.c ft_strlen.c
OBJ_SERVER = $(SRC_SERVER:.c=.o)


all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) -o $(NAME_CLIENT)

$(NAME_SERVER): $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) -o $(NAME_SERVER)

clean:
	rm -rf $(OBJ_CLIENT) $(OBJ_SERVER)

fclean: clean
	rm -rf $(NAME_CLIENT) $(NAME_SERVER)

re: fclean all