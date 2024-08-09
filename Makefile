# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csubires <csubires@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/18 13:48:18 by csubires          #+#    #+#              #
#    Updated: 2024/08/09 12:51:18 by csubires         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C_FILES = main.c	\
		color.c	\
		render.c	\
		moves.c	\
		keys.c	\
		map.c	\
		parse.c	\
		menu.c	\
		utils.c

MLX42_FILE	= lib/MLX42/libmlx42.a
GLFW_FILE	= lib/glfw/src/libglfw3.a
LIBFT_FILE	= lib/libft/libft.a

NAME		= fdf
CC			= gcc
O_DIR		= obj
C_DIR		= source
O_FILES		= $(addprefix $(O_DIR)/,$(C_FILES:%.c=%.o))
PRINT		= echo
GREEN		= \033[0;32m
YELLOW		= \033[1;33m
RED			= \033[1;31m
BLUE		= \033[1;34m
ENDC		= \033[0m

CFLAGS		= -Wall -Werror -Wextra -Wunreachable-code -Ofast
CFLAGS 		+= -D WIN_W=1920 -D WIN_H=1080
LIBS		= -L. -l:$(LIBFT_FILE) -l:$(MLX42_FILE) -l:$(GLFW_FILE)
MLXFLAGS	= -lm -g -pthread -ffast-math
MAKEFLAGS	+= --no-print-directory

# --------------------------------------

all: $(NAME)

$(NAME):	$(O_FILES) $(LIBFT_FILE) $(MLX42_FILE) $(GLFW_FILE)
	@$(PRINT) "$(GREEN)Compiling program executable:$(ENDC)	$@"
	@$(CC) $(O_FILES) -o $@ $(LIBS) $(CFLAGS) $(MLXFLAGS)

$(O_DIR)/%.o:	$(C_DIR)/%.c $(LIBFT_FILE) $(MLX42_FILE) | $(O_DIR)
	@$(PRINT) "\e[1A\e[K$(BLUE)OBJECT:$(ENDC)\t$<	->	$@"
	@$(CC) -c $< -o $@ $(LIBS) $(CFLAGS) $(MLXFLAGS)

$(LIBFT_FILE):
	@make -C "lib/libft"

$(MLX42_FILE):
	@rm lib/MLX42/CMakeCache.txt 2>/dev/null ; true
	@cmake -C "lib/MLX42" 2>/dev/null ; true
	@make -C "lib/MLX42" 2>/dev/null ; true

$(GLFW_FILE):
	@cmake -C "lib/glfw" 2>/dev/null ; true
	@make -C "lib/glfw" 2>/dev/null ; true

$(O_DIR):
	@mkdir -p $(O_DIR)

# --------------------------------------

clean:
	clear
	@$(PRINT) "$(RED)REMOVED!: OBJECTS$(ENDC)"
	@make -C "lib/libft" clean
#@make -C "lib/MLX42" clean
#@make -C "lib/glfw" clean
	@rm -fr $(O_DIR) *.o 2>/dev/null ; true

fclean: clean
	@$(PRINT) "$(RED), LIBRARY, EXECUTABLE$(ENDC)"
	@make -C "lib/libft" fclean
	@rm -rf $(NAME) 2>/dev/null ; true

re:	fclean all

# --------------------------------------

print:
		@$(PRINT) "$(YELLOW)NAME LIBRARY:$(ENDC)\t$(NAME)"
		@$(PRINT) "$(YELLOW)SOURCES:$(ENDC)\t$(C_FILES)"
		@$(PRINT) "$(YELLOW)OBJECTS:$(ENDC)\t$(O_FILES)"
		@nm --print-armap $(LIBFT_FILE) 2>/dev/null ; true
		@nm --print-armap $(MLX42_FILE) 2>/dev/null ; true
		@nm --print-armap $(GLFW_FILE) 2>/dev/null ; true

norm:
	@norminette -R CheckForbiddenSourceHeader **/*.c **/*.h 2>/dev/null ; true

leaks:	CFLAGS += -g -fsanitize=address

.PHONY: all, clean, fclean, re, added, print, norm, leaks
