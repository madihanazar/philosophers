CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

NAME = philo

SRCS = philo.c utils.c philo_create.c philo_init.c philo_cycle.c philo_monitor.c philo_fork.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
