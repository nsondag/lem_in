# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hvromman <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/19 11:36:12 by hvromman          #+#    #+#              #
#    Updated: 2019/04/02 16:33:49 by nsondag          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3
SRCS = srcs/
HEAD = includes/
LIB = libft/
FILE = lem_in.h
H = $(addprefix $(HEAD), $(FILE))
FILES = main.o parser.o parser2.o parser3.o exit.o smallest.o\
		path.o path2.o print.o print2.o crossing_path.o 
OBJ = $(addprefix $(SRCS), $(FILES))
SANITIZE = -fsanitize=address

RED=\033[0;91m
GREEN=\033[0;92m
CYAN=\033[0;96m
NC=\033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB)
	@$(CC) $(CFLAGS) -o $@ $^ -L$(LIB) -lft
	@echo "$(GREEN)$(NAME) compiled$(NC)"

%.o: %.c $(H)
	@$(CC) $(CFLAGS) -c -o $@ $< -I $(HEAD) -I $(LIB)$(HEAD)

clean:
	@make -C $(LIB) clean
	@rm -f $(OBJ)
	@echo "$(RED)$(NAME) cleaned$(NC)"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIB) fclean
	@echo "$(RED)$(NAME) fcleaned$(NC)"

debug: $(OBJ)
	@make -C $(LIB)
	@$(CC) $(CFLAGS) -o $@ $^ -L$(LIB) -lft $(SANITIZE)
	@echo "$(GREEN)$(NAME) compiled$(NC)"

re: fclean all
