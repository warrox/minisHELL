NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3

SRCS = src/main.c src/parser.c
OBJS = $(SRCS:.c=.o)

LIBFTPATH = ./libft/
LIBFT = -L$(LIBFTPATH) -lft
PRINTFPATH = ./Printf/
PRINTF = -L$(PRINTFPATH) -lftprintf

all: $(NAME)

$(NAME): $(OBJS)
		make -C $(LIBFTPATH)
		make -C $(PRINTFPATH)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(PRINTF) $(LIBFT) -lm -lbsd

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFTPATH) -I$(PRINTFPATH) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFTPATH) fclean
	make -C $(PRINTFPATH) fclean

re: fclean all

