# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/22 17:29:22 by fabou-za          #+#    #+#              #
#    Updated: 2022/09/09 18:13:25 by fabou-za         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra -pthread 
NAME = philo
NAME1 = philo_bonus
INC = philo.h
INC_BONUS = philo_bonus.h
SRC = main.c \
	  check_args.c \
	  philos_simulation.c \

BONUS = main_bonus.c \
		simulation_bonus.c \
		check_args_bonus.c \
		utils_bonus.c \

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(BONUS:.c=.o)

all: $(NAME)

bonus: $(NAME1)

$(NAME): $(OBJ) $(INC)
	@$(CC) $(OBJ) -o $(NAME)

$(NAME1): $(OBJ_BONUS) $(INC_BONUS)
	@$(CC) $(OBJ_BONUS) -o $(NAME1)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ) $(OBJ_BONUS)

fclean: clean
	@rm -rf $(NAME) $(NAME1)

re: fclean all
