# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/01 11:22:06 by maraurel          #+#    #+#              #
#    Updated: 2021/10/11 22:30:23 by maraurel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

NAME_BONUS = philo_bonus

SRC_PATH = ./src

SRC_BONUS_PATH = ./bonus/src_bonus

OBJ_PATH = ./obj

OBJ_BONUS_PATH = ./bonus/obj_bonus

SRC = $(notdir $(wildcard ./src/*.c))

SRC_BONUS = $(notdir $(wildcard ./bonus/src_bonus/*.c))

OBJ = $(addprefix $(OBJ_PATH)/, $(SRC:.c=.o))

OBJ_BONUS = $(addprefix $(OBJ_BONUS_PATH)/, $(SRC_BONUS:.c=.o))

CC = clang

FLAGS = -Wall -Wextra -Werror

all: $(NAME) $(OBJ)

bonus: $(NAME_BONUS) $(OBJ_BONUS)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -lpthread -o $(NAME)

$(NAME_BONUS): $(OBJ_BONUS)
	$(CC) $(FLAGS) $(OBJ_BONUS) -lpthread -o $(NAME_BONUS)

$(OBJ_PATH)/%.o:	$(SRC_PATH)/%.c
	$(CC) -g $(FLAGS) -c $< -o $@

$(OBJ_BONUS_PATH)/%.o:	$(SRC_BONUS_PATH)/%.c
	$(CC) -g $(FLAGS) -c $< -o $@

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(NAME_BONUS)

clean:
	@$(RM) $(OBJ_PATH)/*.o
	@$(RM) $(OBJ_BONUS_PATH)/*.o

re: fclean all

git:
	git add .
	git commit -m "Update"
	git push


