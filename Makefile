NAME = philo

SRC_DIR = ./
SRC = main.c

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
	ctags $(SRC)

clean:
	$(RM) $(OBJ)
	$(RM) tags

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re sanitize tag
