NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

SRCS = src/main.c src/parsing.c
OBJS = $(SRCS:.c=.o)

LIBFTPATH = ./libft/
LIBFT = -L$(LIBFTPATH)
PRINTFPATH = ./Printf/
PRINTF = -L$(PRINTFPATH)
all: $(NAME)

$(NAME): $(OBJS)
		make -C $(LIBFTPATH)
		make -C $(PRINTFPATH)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(PRINTF) -lftprintf $(LIBFT) -lm -lbsd

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFTPATH) -I$(PRINTFPATH) -c $< -o $@

clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFTPATH) fclean
	make -C $(PRINTFPATH) fclean

re: fclean all
