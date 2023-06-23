# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/01 09:55:43 by gpouzet           #+#    #+#              #
#    Updated: 2023/06/23 12:51:09 by gpouzet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 	= clang

FLAGS = -Wall -Wextra -Werror -g

NAME = philo

NAMEB = philo_bonus

SRC = src/main.c src/parser.c src/tools.c src/set_data.c src/philo.c \

BNS =

OBJ	= $(SRC:.c=.o)

OBJB = $(BNS:.c=.o)

%.o: %.c
	@$(CC) $(FLAGS) -o $@ -c $<
	@echo -n "\\r\033[2K"
	@echo -n "\\r\033[1;33m[compiling...]"$<

all: $(NAME)

bonus: $(NAMEB)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -lpthread -o $(NAME) 
	@echo -n "\\r\033[2K"
	@echo "\033[1;32m[executable created]"

$(NAMEB): $(OBJB)
	@$(CC) $(FLAGS) $(OBJB) -o $(NAMEB) 
	@echo -n "\\r\033[2K"
	@echo "\033[1;32m[executable bonus created]"

clean:
	@rm -rf $(OBJ) $(OBJB)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(NAMEB)
	@echo "\033[1;32m[Programe deleted]"

re: fclean all

.PHONY: all clean fclean re bonus
