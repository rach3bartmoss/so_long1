# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/10 20:59:32 by dopereir          #+#    #+#              #
#    Updated: 2024/10/25 10:08:14 by dopereir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libft.a

Sources = $(wildcard *.c)

Compiler = cc $(Flags) -c

Flags = -Wall -Wextra -Werror

mylib = ar rc $(NAME)

ranlib = ranlib $(NAME)

remove = rm -f

O_FILES = $(Sources:.c=.o)
O_BONUS = $(Bonus:.c=.o)

GREEN = \033[0;32m
RESET = \033[0m

all: compile_msg $(NAME)

$(NAME): $(O_FILES)
	@$(mylib) $(O_FILES)
	@$(ranlib)

compile_msg:
	@echo "$(GREEN)Compiling libft...$(RESET)"

$(O_FILES): %.o: %.c
	@$(Compiler) -o $@ $<

bonus: $(O_BONUS)
	@$(mylib) $(O_BONUS)
	@$(ranlib)

$(O_BONUS): %.o: %.c
	@$(Compiler) -o $@ $<

clean:
	@$(remove) $(O_FILES) $(O_BONUS)

fclean:	clean
	@$(remove) $(NAME)

re:	fclean	all

.PHONY: clean fclean re bonus
