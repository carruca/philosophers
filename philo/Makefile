NAME = philo

UTILS_DIR = utils_ft/
UTILS_SRC = ft_calloc.c \
			ft_strdigit.c \
			ft_isdigit.c \
			ft_strneg.c \
			ft_strlen.c \
			ft_atoi.c

SRC_DIR	= ./
SRC := $(SRC) \
	   $(addprefix $(UTILS_DIR), $(UTILS_SRC)) \
	   main.c \
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
	   thread_join_loop.c \
	   chips_init.c \
	   count_eat.c \
	   diner_life_loop.c \
  	   dsleep.c \
	   eating.c \
	   give_chip_to_right.c \
	   hold_chopsticks.c \
	   philo_free.c \
	   print_status.c \
	   set_chopsticks.c \
	   set_dead.c \
	   sleeping.c

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
