# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mschiman <mschiman@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/07 20:03:54 by mschiman          #+#    #+#              #
#    Updated: 2022/08/14 13:53:15 by mschiman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	./main.c \
		./init.c \
		./helpers.c \
		./check_status.c \
		./routine.c \
		./print.c
		
NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror
#Could make it faster add at the end of line 22:: -g -O3
#Data Race check #1
#						 add at the end of line 22: -fsanitize=thread
#Data Race check #2 (not an M1 Mac):
#						 valgrind --tool=helgrind ./philo 5 310 200 200
#Leaks check on Mac: Leaks --atExit -- ./philo ....
#Leaks check on Linux: valgrind ./philo ...
OBJS = ${SRC:.c=.o}

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(SRC) -pthread -o $(NAME)
		
all:	$(NAME)

clean:
	@rm -f ${OBJS}

fclean: clean
	-rm $(NAME)

re: fclean all

.PHONY: clean fclean re all