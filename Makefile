
SRC = 	./main.c \
		./helpers.c \
		./error_handler.c
		
NAME = philosophers
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -O3 -fsanitize=thread
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