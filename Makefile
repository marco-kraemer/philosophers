# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/01 11:22:06 by maraurel          #+#    #+#              #
#    Updated: 2021/07/08 08:29:55 by maraurel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers

SRC_PATH = ./src

OBJ_PATH = ./obj

SRC = $(notdir $(wildcard ./src/*.c))
OBJ = $(addprefix $(OBJ_PATH)/, $(SRC:.c=.o))

CC = clang

FLAGS = #-Wall -Wextra -Werror

all: $(NAME) $(OBJ)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -lpthread -o $(NAME)


$(OBJ_PATH)/%.o:	$(SRC_PATH)/%.c
	@$(CC) -g $(FLAGS) -c $< -o $@

fclean: clean
	@$(RM) $(NAME)

clean:
	@$(RM) $(OBJ_PATH)/*.o

re: fclean all

run: all
	@./$(NAME)

git:
	git add .
	git commit -m "Update"
	git push


