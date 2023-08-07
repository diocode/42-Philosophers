# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/03 13:01:56 by digoncal          #+#    #+#              #
#    Updated: 2023/08/03 13:01:56 by digoncal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LIBFT = libs/libft/libft.a

NAME = philo

SRC = src/main.c src/init.c src/free.c src/utils.c

OBJ = $(SRC:.c=.o)

all: deps $(NAME)
	
deps:
	$(MAKE) -C ./libs/libft
	
$(NAME): $(OBJ) $(DEPS)
	$(CC) $(CFLAGS) -pthread $(OBJ) $(LIBFT) -o $(NAME)

clean:
	$(MAKE) $@ -C ./libs/libft
	@rm -rf $(OBJ)

fclean: clean
	$(MAKE) $@ -C ./libs/libft
	@rm -rf $(NAME)

re: fclean all
	$(MAKE) re -C ./libs/libft
