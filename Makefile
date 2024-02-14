NAME = philo

CC = cc

FLAGS = -Wall -Wextra -Wextra -pthread

LEAKFLAGS = -g3 -fsanitize=pthread

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

fclean:
	$(RM) $(NAME)

re: fclean all