# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 15:09:03 by cyferrei          #+#    #+#              #
#    Updated: 2024/05/07 14:40:13 by cyferrei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
RM = rm -rf
CFLAGS = -Wall -Werror -Wextra -g3

LIBFT_MINISHELL_PATH = libft
LIBFT_MINISHELL = libft/libft.a

FT_PRINTF_PATH = ft_printf
FT_PRINTF = ft_printf/ft_printf.a

BOLD    = \e[1m
FADE    = \e[2m
ITA     = \e[3m
BLINK   = \e[5m
GREEN   = \e[38;5;76m
RED     = \e[38;5;196m
YELLOW  = \e[38;5;227m
ORANGE  = \e[38;5;208m
PURPLE  = \e[38;5;201m
LBLUE   = \e[38;5;45m
BLUE    = \e[38;5;27m
INDI    = \e[38;5;91m
SPINK   = \e[38;5;225m
PEACH   = \e[38;5;223m
GREY    = \e[38;5;254m
RESET   = \e[00m

SOURCE = ./src/
MAIN = main.c parser.c
LST = lst_custom.c lst_custom_1.c 
PROMPT = prompt.c prompt_utils.c
MINISHELL = $(addprefix $(SOURCE), $(MAIN) $(LST) $(PROMPT))

SRC = $(MINISHELL)
OBJS = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
		@echo "$(BOLD)Linking...$(RESET)"
		@make -sC $(LIBFT_MINISHELL_PATH)
		@make -sC $(FT_PRINTF_PATH)
		$(CC) $(CFLAGS) -lreadline $(OBJS) $(FT_PRINTF) $(LIBFT_MINISHELL) -o $(NAME)
		@echo "$(GREEN)Executable '$(NAME)' created successfully!$(RESET)"
		
		@echo "\033[35m░▒▓██████████████▓▒░░▒▓█▓▒░▒▓███████▓▒░░▒▓█▓▒░░▒▓███████▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓████████▓▒░▒▓█▓▒░      ░▒▓█▓▒░        \033[0m"
		@echo "\033[35m░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░        \033[0m"
		@echo "\033[35m░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░        \033[0m"
		@echo "\033[35m░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓██████▓▒░░▒▓████████▓▒░▒▓██████▓▒░ ░▒▓█▓▒░      ░▒▓█▓▒░        \033[0m"
		@echo "\033[35m░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░        \033[0m"
		@echo "\033[35m░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░        \033[0m"
		@echo "\033[35m░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓███████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓████████▓▒░▒▓████████▓▒░▒▓████████▓▒░\033[0m"
		
%.o: %.c
	@echo "$(BOLD)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)$@ compiled successfully!$(RESET)"

clean:
	@echo "$(BOLD)Cleaning object files...$(RESET)"
	$(RM) $(OBJS)
	@make -s clean -C $(LIBFT_MINISHELL_PATH)
	@make -s clean -C $(FT_PRINTF_PATH)
	@echo "$(GREEN)Object files cleaned successfully!$(RESET)"
	
fclean: clean
	@echo "$(BOLD)Cleaning object files...$(RESET)"
	@make -s fclean -C $(LIBFT_MINISHELL_PATH)
	@make -s fclean -C $(FT_PRINTF_PATH)
	$(RM) $(NAME)
	@echo "$(GREEN)Executable cleaned successfully!$(RESET)"
	
leak:
	valgrind --suppressions=ignore_readline --trace-children=yes    \
    --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes -q  \
    ./minishell
	
re: fclean all

.PHONY: all clean fclean re