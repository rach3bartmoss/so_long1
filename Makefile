#target: dependencies / prerequisites
#	command
#	command...


#to prevent relinks we need to create prerequisites for the target

NAME = so_long

#SOURCES = $(wildcard sources/*.c)
SOURCES = main.c clean_close.c ft_init.c map_loading.c \
			map_validation.c tile_management.c \
			player_management.c player_mechanics.c \
			enemies_management.c enemies_mechanics.c \
			enemies_management_helper.c dfs_path_validation.c \
			player_management_helper.c player_mechanics_helper.c \
			player_mechanics_helper2.c enemies_mechanics_helper.c\
			errors_messages.c \

OBJECTS = $(SOURCES:.c=.o)
CC = gcc
FLAGS = -Wall -Wextra -Werror

GREEN = \033[0;32m
RESET = \033[0m

LIBFT_DIR = ./libraries/libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I./ -I$(LIBFT_DIR) -I./sources -I/usr/local/include
LINKS = -L/usr/local/lib -L$(LIBFT_DIR) -lmlx -lXext -lX11 -lm

all: $(LIBFT) compile_solong $(NAME) #this prevents relinking if the executable is up to date

compile_solong:
	@echo "$(GREEN)Compiling so_long...$(RESET)"

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

$(NAME): $(OBJECTS) $(LIBFT) #this prevents relinking if the object files are up to date
	@$(CC) $(OBJECTS) -o $(NAME) $(FLAGS) $(LINKS) $(LIBFT)

%.o: %.c so_long.h
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

valgrind : $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) test2.ber

clean:
	rm -f $(OBJECTS)
	@$(MAKE) -s -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re valgrind
