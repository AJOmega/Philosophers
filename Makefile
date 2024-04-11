NAME = philo

CC = cc -g

FLAGS = -Wall -Wextra -Wextra -pthread

LEAKFLAGS = -g3 -fsanitize=thread

RM = rm -rf

SRCS = main.c error_handle.c utils.c \
		init.c launcher.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(FLAGS) $(OBJS) -o philo

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all