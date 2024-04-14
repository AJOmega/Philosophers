NAME = philo

CC = cc

FLAGS = -Wall -Wextra -Wextra -pthread

LEAKFLAGS = -g3 -fsanitize=thread

RM = rm -rf

SRCS = main.c error_handle.c atoi.c time_manager.c \
		init.c eating.c actions.c exit.c threads.c\

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