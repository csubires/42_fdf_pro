# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csubires <csubires@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/18 13:48:18 by csubires          #+#    #+#              #
#    Updated: 2024/07/25 19:46:21 by csubires         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C_FILES = main.c	\
		color.c	\
 		color_utils.c	\
		render.c	\
		render_utils.c	\
		keys.c	\
		map.c	\
		parse.c	\
		utils.c

MLX42_FILE	= mlx42/libmlx42.a
GLFW_FILE	= mlx42/libglfw3.a
LIBFT_FILE	= libft/libft.a

NAME		= fdf
NAME_C		= $(C_DIR)/main.c
CC			= gcc
O_DIR		= obj
C_DIR		= source
O_FILES		= $(addprefix $(O_DIR)/,$(C_FILES:%.c=%.o))
PRINT		= echo
GREEN		= \033[0;32m
YELLOW		= \033[1;33m
RED			= \033[1;31m
ENDC		= \033[0m

INCLUDES	= -I ./mlx42/include/MLX42	\
		-I ./libft	\
		-I ./include	\
		-I ./source

MAKEFLAGS	+= --no-print-directory
CFLAGS		= -Wall -Werror -Wextra -Wunreachable-code -Ofast
CFLAGS 		+= -D WIN_W=1920 -D WIN_H=1080 -g
CFLAGS 		+= $(INCLUDES)
MLXFLAGS	= -L. -l:$(LIBFT_FILE) -l:./mlx42/libmlx42.a -l:./mlx42/libglfw3.a
# --------------------------------------

all: $(NAME)

$(NAME):	$(O_FILES) $(LIBFT_FILE)
	@$(PRINT) "$(GREEN)EXECUTABLE:$(ENDC)	$@"
	@$(CC) $(O_FILES) -o $@ -pthread -lm -L. -l:$(LIBFT_FILE) -l:./mlx42/libmlx42.a -l:./mlx42/libglfw3.a

$(O_DIR)/%.o:	$(C_DIR)/%.c $(LIBFT_FILE) | $(O_DIR)
	@$(CC) -c $< -o $@ -L -l:$(LIBFT_FILE) $(MLXFLAGS) -lm

$(LIBFT_FILE):
	@make -C "libft" added

$(MLX42_FILE):
	@make -C "mlx42" 2>/dev/null ; true

$(O_DIR):
	@mkdir -p $(O_DIR)

# --------------------------------------

clean:
	clear
	@$(PRINT) "$(RED)REMOVED!: OBJECTS$(ENDC)"
	@make -C "libft" clean
	@make -C "mlx42" clean
	@rm -fr -v $(O_DIR) *.o 2>/dev/null ; true

fclean: clean
	@$(PRINT) "$(RED), LIBRARY, EXECUTABLE$(ENDC)"
	@make -C "libft" fclean
	@rm -rf -v $(NAME) $(NAME) 2>/dev/null ; true

re:	fclean all

# --------------------------------------

print:
		@$(PRINT) "$(YELLOW)NAME LIBRARY:$(ENDC)\t$(NAME)"
		@$(PRINT) "$(YELLOW)SOURCES:$(ENDC)\t$(C_FILES)"
		@$(PRINT) "$(YELLOW)OBJECTS:$(ENDC)\t$(O_FILES)"
		@nm --print-armap $(NAME) 2>/dev/null ; true

norm:
	@norminette -R CheckForbiddenSourceHeader **/*.c **/*.h 2>/dev/null ; true

leaks:	CFLAGS += -g -fsanitize=address

.PHONY: all, clean, fclean, re, added, print, norm, leaks
