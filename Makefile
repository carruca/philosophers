NAME = philo

SRC_DIR = ./
SRC = main.c \
	  ft_calloc.c \
	  ft_strdigit.c \
	  ft_isdigit.c \
	  ft_strneg.c \
	  error.c \
	  assign_chopsticks.c \
	  assign_locks.c \
	  diner_create.c \
	  philo_create.c \
	  get_msec_since_start.c \
	  get_time.c \
	  mutex_destroy_loop.c \
	  mutex_init_loop.c \
	  thread_create_loop.c \
	  thread_join_loop.c

OBJ = $(SRC:.c=.o)

INC = -I.
LPTHREAD = -lpthread

DEBUG = -g3
SANITIZE = -fsanitize=address

CFLAGS = -Wall -Werror -Wextra $(INC) -O3 $(COMMON)
COMMON =
LDFLAGS = $(COMMON)
CC = gcc
MAKE = make
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LPTHREAD) $(LDFLAGS)

sanitize: COMMON += $(SANITIZE) $(DEBUG)
sanitize: all

tag:
	ctags $(SRC) philo.h

clean:
	$(RM) $(OBJ)
	$(RM) tags

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re sanitize tag
