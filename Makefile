# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pprussen <pprussen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/30 16:46:35 by mschiman          #+#    #+#              #
#    Updated: 2022/08/25 15:56:22 by pprussen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = 	src/main.c \
		src/init.c \
		src/helpers.c \
		src/error_clean.c \
		src/routine.c \
		src/prints.c
		
NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror #-g -O3 -fsanitize=thread
OBJS = ${SRC:.c=.o}

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(SRC) -pthread -o $(NAME)
		
all:	$(NAME)

clean:
	@rm -f ${OBJS}

fclean: clean
	-rm $(NAME)
	-rm ./src/*.o

re: fclean all

.PHONY: clean fclean re all