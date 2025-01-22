# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ptelo-de <ptelo-de@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/21 17:57:19 by ptelo-de          #+#    #+#              #
#    Updated: 2024/04/24 21:42:35 by ptelo-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC = ft_atoi.c     ft_isalpha.c  ft_itoa.c	 ft_memmove.c	  ft_putnbr_fd.c  ft_strdup.c	 ft_strlcpy.c  ft_strnstr.c  ft_tolower.c \
ft_bzero.c    ft_isascii.c  ft_memchr.c  ft_memset.c	  ft_putstr_fd.c  ft_striteri.c  ft_strlen.c   ft_strrchr.c  ft_toupper.c \
ft_calloc.c   ft_isdigit.c  ft_memcmp.c  ft_putchar_fd.c  ft_split.c	  ft_strjoin.c	 ft_strmapi.c  ft_strtrim.c \
ft_isalnum.c  ft_isprint.c  ft_memcpy.c  ft_putendl_fd.c  ft_strchr.c	  ft_strlcat.c	 ft_strncmp.c  ft_substr.c 
BONUS = ft_lstnew.c	ft_lstadd_front.c	ft_lstsize.c	ft_lstlast.c	ft_lstadd_back.c	ft_lstdelone.c ft_lstclear.c	ft_lstiter.c	ft_lstmap.c
OBJ_B = $(BONUS:.c=.o)
OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

all: $(NAME)

bonus: $(NAME) $(OBJ_B)
	ar rsc $(NAME) $(OBJ_B)

$(NAME): $(OBJ)
	@ar rsc $(NAME) $(OBJ)
	@echo "compilled"

run: all
	cc test.c libft.a
	valgrind ./a.out

clean:
	@rm -f $(OBJ) $(OBJ_B)

fclean: clean
	@rm -f $(NAME)

re: fclean all


