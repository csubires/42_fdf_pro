#!/bin/zsh

PROJECT="libft"
REPO_ID42="intra-uuid-5cb9b052-0cc8-414a-9d53-5856ffd62e2d-5626596-csubires"
# ----------------------------------
REPO_SIM="../_INTRA/${PROJECT}_GIT/"
REPO_G42="/Users/csubires/Documents/cursus/${PROJECT}/${REPO_ID42}/"

# ---------------------------------- FILES (MAKEFILE && HEADER.H && THIS)

HEADERS=(
	libft.h
)

MANDATORY=(
	ft_isalpha.c
	ft_isdigit.c
	ft_isalnum.c
	ft_isascii.c
	ft_isprint.c
	ft_strlen.c
	ft_memset.c
	ft_bzero.c
	ft_memcpy.c
	ft_memmove.c
	ft_strlcpy.c
	ft_strlcat.c
	ft_toupper.c
	ft_tolower.c
	ft_strchr.c
	ft_strrchr.c
	ft_strncmp.c
	ft_memchr.c
	ft_memcmp.c
	ft_strnstr.c
	ft_atoi.c
	ft_calloc.c
	ft_strdup.c
	ft_substr.c
	ft_strjoin.c
	ft_strtrim.c
	ft_split.c
	ft_itoa.c
	ft_strmapi.c
	ft_striteri.c
	ft_putchar_fd.c
	ft_putstr_fd.c
	ft_putendl_fd.c
	ft_putnbr_fd.c
)

UTILS=(
	ft_isspace.c
	ft_nbrlen.c
	ft_isinset.c
	ft_free_ptr.c
	printf.c
	ft_putnbr_base.c
	get_next_line.c
	ft_minimum.c
	ft_maximum.c
	ft_abs.c
	ft_free_split.c
)

BONUS=(
	ft_lstnew.c
	ft_lstadd_front.c
	ft_lstsize.c
	ft_lstlast.c
	ft_lstadd_back.c
	ft_lstdelone.c
	ft_lstclear.c
	ft_lstiter.c
	ft_lstmap.c
)

OTHERS=(Makefile)

ALL_FILES=(
	$HEADERS[@]
	$MANDATORY[@]
	$UTILS[@]
	$BONUS[@]
	$OTHERS[@]
)

# ----------------------------------

FLAGS=(-Wall -Wextra -Werror) #  -ldl -g -fsanitize=address
