#/* ************************************************************************** */
#/*                                                                            */
#/*                                                        :::      ::::::::   */
#/*   Makefile                                           :+:      :+:    :+:   */
#/*                                                    +:+ +:+         +:+     */
#/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
#/*                                                +#+#+#+#+#+   +#+           */
#/*   Created: 2024/04/10 16:37:51 by csubires          #+#    #+#             */
#/*   Updated: 2024/04/22 15:48:59 by csubires         ###   ########.fr       */
#/*                                                                            */
#/* ************************************************************************** */

C_FILES	= ft_strlen.c	\
		ft_calloc.c	\
		ft_split.c	\
		ft_free_ptr.c	\
		ft_strchr.c	\
		ft_free_split.c	\
		ft_strjoin.c	\
		ft_get_next_line.c	\
		ft_strlcpy.c	\
		ft_substr.c \
		ft_maximum.c	\
		ft_bzero.c	\
		ft_strdup.c

NAME		= libft.a
HEADER		= libft.h
CC		= clang
AR		= ar -crs
CFLAGS 		= -Wall -Werror -Wextra -fPIE -I$(H_FILES)
H_FILES		= .
O_DIR		= obj
C_DIR		= .
O_DIR_BONUS	= obj_bonus
C_DIR_BONUS	= .
O_FILES		= $(addprefix $(O_DIR)/,$(C_FILES:%.c=%.o))
O_UTILS		= $(addprefix $(O_DIR)/,$(C_UTILS:%.c=%.o))
O_ADDED		= $(addprefix $(O_DIR)/,$(C_ADDED:%.c=%.o))
O_BONUS		= $(addprefix $(O_DIR_BONUS)/,$(C_BONUS:%.c=%.o))
PRINT		= echo
GREEN		= \033[0;32m
YELLOW		= \033[1;33m
RED			= \033[1;31m
ENDC		= \033[0m
# --------------------------------------

all:		$(NAME)

$(NAME):	$(O_FILES) $(O_UTILS) | $(O_DIR)
	@$(PRINT) "$(YELLOW)BUILDING LIBRARY:$(ENDC)\t$(NAME)"
	@$(AR) $(NAME) $(O_FILES) $(O_UTILS)

$(O_DIR)/%.o:	$(C_DIR)/%.c | $(O_DIR)
	@$(PRINT) "$(GREEN)OBJECT:$(ENDC)\t$<		->	$@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(O_DIR):
	@mkdir -p $(O_DIR)


# --------------------------------------

clean:
	clear
	@$(PRINT) "$(RED)REMOVED!: OBJECTS$(ENDC)"
	@rm -fr $(O_DIR) $(O_DIR_BONUS) *.o

fclean: clean
	@$(PRINT) "$(RED), LIBRARY, EXECUTABLE$(ENDC)"
	@rm -f $(NAME) 2>/dev/null ; true

re:	fclean all

# --------------------------------------

print:
		@$(PRINT) "$(YELLOW)NAME LIBRARY:$(ENDC)\t$(NAME)"
		@$(PRINT) "$(YELLOW)SOURCES:$(ENDC)\t$(C_FILES)"
		@$(PRINT) "$(YELLOW)OBJECTS:$(ENDC)\t$(O_FILES)"
		@$(PRINT) "$(YELLOW)SOURCES UTILS:$(ENDC)\t$(C_UTILS)"
		@$(PRINT) "$(YELLOW)OBJECTS UTILS:$(ENDC)\t$(O_UTILS)"
		@$(PRINT) "$(YELLOW)SOURCES ADDED:$(ENDC)\t$(C_ADDED)"
		@$(PRINT) "$(YELLOW)OBJECTS ADDED:$(ENDC)\t$(O_ADDED)"
		@$(PRINT) "$(YELLOW)SOURCES BONUS:$(ENDC)\t$(C_BONUS)"
		@$(PRINT) "$(YELLOW)OBJECTS BONUS:$(ENDC)\t$(O_BONUS)"
		@nm --print-armap $(NAME) 2>/dev/null ; true

norm:
		@norminette -R CheckForbiddenSourceHeader $(C_FILES) $(C_UTILS) $(HEADER) 2>/dev/null ; true

leaks:	CFLAGS += -g -fsanitize=address

.PHONY: all, clean, fclean, re, bonus, added, print, norm, leaks
