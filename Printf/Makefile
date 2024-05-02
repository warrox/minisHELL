# Nom de la cible finale
NAME = libftprintf.a

# Compilateur
CC = cc

# Flags de compilation
CFLAGS = -Wall -Wextra -Werror

# Fichiers sources
SRCS = ft_printf.c ft_printf_utils.c ft_printf_hex.c

# Fichiers objets (correspondant aux fichiers sources)
OBJS = $(SRCS:.c=.o)

# Règle par défaut
all: $(NAME)

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
OBJS = ${SRCS:.c=.o}
# Comment créer la bibliothèque statique
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
	@echo "$(MAGENTA)     /\  \         /\  \          ___        /\__\         /\  \         /\  \    $(DEF_COLOR)"
	@echo "$(MAGENTA)    /::\  \       /::\  \        /\  \      /::|  |        \:\  \       /::\  \   $(DEF_COLOR)"
	@echo "$(MAGENTA)   /:/\:\  \     /:/\:\  \       \:\  \    /:|:|  |         \:\  \     /:/\:\  \  $(DEF_COLOR)"
	@echo "$(MAGENTA)  /::\~\:\  \   /::\~\:\  \      /::\__\  /:/|:|  |__       /::\  \   /::\~\:\  \ $(DEF_COLOR)"
	@echo "$(MAGENTA) /:/\:\ \:\__\ /:/\:\ \:\__\  __/:/\/__/ /:/ |:| /\__\     /:/\:\__\ /:/\:\ \:\__\$(DEF_COLOR)"
	@echo "$(MAGENTA) \/__\:\/:/  / \/_|::\/:/  / /\/:/  /    \/__|:|/:/  /    /:/  \/__/ \/__\:\ \/__/$(DEF_COLOR)"
	@echo "$(MAGENTA)      \::/  /     |:|::/  /  \::/__/         |:/:/  /    /:/  /           \:\__\  $(DEF_COLOR)"
	@echo "$(MAGENTA)       \/__/      |:|\/__/    \:\__\         |::/  /     \/__/             \/__/  $(DEF_COLOR)"
	@echo "$(MAGENTA)                  |:|  |       \/__/         /:/  /                               $(DEF_COLOR)"
	@echo "$(MAGENTA)                   \|__|                     \/__/                                $(DEF_COLOR)"

# Règle pour créer les fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers objets
clean:
	rm -f $(OBJS)

# Règle pour nettoyer tout (y compris la bibliothèque)
fclean: clean
	rm -f $(NAME)

# Règle pour recompiler tout
re: fclean all

# Marquer les cibles comme PHONY (ne correspondant pas à un fichier)
.PHONY: all clean fclean re
