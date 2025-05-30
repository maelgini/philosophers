NAME		=	philo
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra

LIBFT_DIR	=	libft
LIBFT		=	$(LIBFT_DIR)/libft.a

SRC_DIR		=	src

SRCS		=	src/threads.c src/utils.c src/main.c src/states.c src/routine.c \
				src/parsing.c src/forks.c src/time.c \

OBJS		=	$(SRCS:.c=.o)

.PHONY: all clean fclean re bonus

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

bonus: $(LIBFT)
	$(CC) $(CFLAGS) $(LIBFT) -o $(NAME)

clean:
	$(RM) $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all