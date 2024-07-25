#!/bin/zsh

PROJECT="fdf"
REPO_ID42="intra-uuid-ae497e2f-df69-4141-8325-e0d04aad1b3e-5797947-csubires"
# ----------------------------------
REPO_SIM="../_INTRA/${PROJECT}_GIT/"
REPO_G42="/home/csubires/Documents/_INTRA/${PROJECT}/${REPO_ID42}/"

# ---------------------------------- FILES (MAKEFILE && HEADER.H && THIS)

FOLDERS=(
	libft
	include
	source
	bonus
)

HEADERS=(
	include/config.h
	include/structs.h
	include/fdf.h
	bonus/colors_bonus.h
	bonus/config_bonus.h
	bonus/keys_bonus.h
	bonus/structs_bonus.h
	bonus/fdf_bonus.h
	libft/libft.h
)

MANDATORY=(
	source/main.c
	source/map.c
	source/parse.c
	source/render.c
	source/utils.c
)

UTILS=()

BONUS=(
	bonus/color_bonus.c
	bonus/color_utils_bonus.c
	bonus/keys_bonus.c
	bonus/main_bonus.c
	bonus/map_bonus.c
	bonus/parse_bonus.c
	bonus/render_bonus.c
	bonus/render_utils_bonus.c
	bonus/utils_bonus.c
)

OTHERS=(
	Makefile
	libft/Makefile
)

LIBFT=(
	libft/ft_isascii.c
	libft/ft_lstdelone.c
	libft/ft_memmove.c
	libft/ft_putstr_fd.c
	libft/ft_strlen.c
	libft/ft_atoi_base.c
	libft/ft_isdigit.c
	libft/ft_lstiter.c
	libft/ft_memset.c
	libft/ft_split.c
	libft/ft_strmapi.c
	libft/ft_atoi.c
	libft/ft_isinset.c
	libft/ft_lstlast.c
	libft/ft_nbrlen.c
	libft/ft_strchr.c
	libft/ft_strncmp.c
	libft/ft_bzero.c
	libft/ft_isprint.c
	libft/ft_lstmap.c
	libft/ft_printf.c
	libft/ft_strdup.c
	libft/ft_strnstr.c
	libft/ft_calloc.c
	libft/ft_isspace.c
	libft/ft_lstnew.c
	libft/ft_putchar_fd.c
	libft/ft_striter.c
	libft/ft_strrchr.c
	libft/ft_free_ptr.c
	libft/ft_itoa.c
	libft/ft_lstsize.c
	libft/ft_putendl_fd.c
	libft/ft_striteri.c
	libft/ft_strtrim.c
	libft/ft_get_next_line.c
	libft/ft_lstadd_back.c
	libft/ft_memchr.c
	libft/ft_putnbr_base.c
	libft/ft_strjoin.c
	libft/ft_substr.c
	libft/ft_isalnum.c
	libft/ft_lstadd_front.c
	libft/ft_memcmp.c
	libft/ft_putnbr_fd.c
	libft/ft_strlcat.c
	libft/ft_tolower.c
	libft/ft_isalpha.c
	libft/ft_lstclear.c
	libft/ft_memcpy.c
	libft/ft_strlcpy.c
	libft/ft_toupper.c
	libft/ft_minimum.c
	libft/ft_maximum.c
	libft/ft_abs.c
	libft/ft_free_split.c
)

ALL_FILES=(
	$FOLDERS[@]
	$HEADERS[@]
	$MANDATORY[@]
	$UTILS[@]
	$BONUS[@]
	$OTHERS[@]
	$LIBFT[@]
)

FLAGS=(-Wall -Wextra -Werror -g) #  -ldl -g -fsanitize=address
