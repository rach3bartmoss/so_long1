#target: dependencies / prerequisites
#	command
#	command...


#to prevent relinks we need to create prerequisites for the target

NAME = so_long

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
FLAGS = -Wall -Wextra -Werror -fPIE
LINK_FLAGS = -pie

GREEN = \033[0;32m
RESET = \033[0m

LIBFT_DIR = ./libraries/libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ./libraries/mlx
MLX = $(MLX_DIR)/libmlx.a
MLX_TGZ = ./libraries/minilibx-linux.tgz

INCLUDES = -I./ -I$(LIBFT_DIR) -I./sources -I$(MLX_DIR) -I/usr/local/include
LINKS = -L$(MLX_DIR) -L$(LIBFT_DIR) -lmlx -lXext -lX11 -lm

all: $(LIBFT) $(MLX) compile_solong $(NAME) #this prevents relinking if the executable is up to date

compile_solong:
	@echo "$(GREEN)Compiling so_long...$(RESET)"

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR) CFLAGS="$(FLAGS)"

$(MLX_DIR):
	@echo "$(GREEN)Extracting minilibx...$(RESET)"
	@mkdir -p $(MLX_DIR)
	@tar -xzf $(MLX_TGZ) -C $(MLX_DIR) --strip-components=1

$(MLX): $(MLX_DIR)
	@echo "$(GREEN)Compiling minilibx...$(RESET)"
	@$(MAKE) -s -C $(MLX_DIR) > /dev/null 2>&1

$(NAME): $(OBJECTS) $(LIBFT) $(MLX)#this prevents relinking if the object files are up to date
	@$(CC) $(OBJECTS) -o $(NAME) $(FLAGS) $(LINK_FLAGS) $(LINKS) $(LIBFT)

%.o: %.c so_long.h
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

valgrind : $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) maps/test2.ber

clean:
	rm -f $(OBJECTS)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@$(MAKE) -s -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@$(MAKE) -s -C $(MLX_DIR) clean
	@rm -rf $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re valgrind compile_solong
