NAME		=	philo
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra

SRC_DIR		=	src

SRCS		=	src/threads.c src/utils.c src/main.c src/states.c src/states2.c \
				src/routine.c src/parsing.c src/forks.c src/time.c src/monitor.c \

OBJS		=	$(SRCS:.c=.o)

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all