# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/13 08:59:31 by kcosta            #+#    #+#              #
#    Updated: 2018/08/15 14:38:57 by kcosta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := ft_nm

CC		:= gcc
FLAGS	:= -Wall -Wextra -Werror -g

SRCS_FILES		:=	ft_nm.c			\
					ft_strlen.c		\
					ft_strcmp.c		\
					ft_strcpy.c		\
					ft_strncpy.c	\
					ft_strdup.c

HEADERS_FILES 	:=	ft_nm.h

SRCS_PATH	:= sources/
SRCS		:= $(addprefix $(SRCS_PATH), $(SRCS_FILES))
OBJS_PATH	:= objs/
OBJS		:= $(addprefix $(OBJS_PATH), $(SRCS_FILES:.c=.o))

INCLUDES_PATH	:= includes/
INCLUDES		:= -I $(INCLUDES_PATH)
HEADERS			:= $(addprefix $(INCLUDES_PATH), $(HEADERS_FILES))

.PHONY: all clean fclean re

all: $(NAME)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c $(HEADERS)
	@mkdir $(OBJS_PATH) 2> /dev/null || true
	$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -lncurses $(OBJS) -o $@

clean:
	@rm -fv $(OBJS)
	@rmdir $(OBJS_PATH) 2> /dev/null || true

fclean: clean
	@rm -fv $(NAME)

re: fclean all
