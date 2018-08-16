# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/16 19:08:49 by kcosta            #+#    #+#              #
#    Updated: 2018/08/16 19:21:07 by kcosta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ========== Editable ========== #
NM		:= ft_nm
OTOOL	:= ft_otool
# ============================== #

# ========== Standard ========== #
CC		:= gcc
FLAGS	:= -g -Wall -Wextra -Werror #-g -fsanitize=address
# ============================== #

# =========== Files ============ #
NM_SRCS_FILES		:=	ft_nm.c		\
						utils.c		\
						sections.c	\
						ppc.c		\
						archive.c	\
						macho32.c	\
						macho64.c	\
						fat32.c		\
						fat64.c		\
						ft_utils.c
OTOOL_SRCS_FILES	:=	ft_otool.c

NM_HEADERS_FILES	:=	ft_nm.h
OTOOL_HEADERS_FILES	:=	ft_otool.h
# ============================== #

# ========== Sources =========== #
NM_PATH		:= sources/nm/
OTOOL_PATH	:= sources/otool/
NM_SRCS		:= $(addprefix $(NM_PATH), $(NM_SRCS_FILES))
OTOOL_SRCS	:= $(addprefix $(OTOOL_PATH), $(OTOOL_SRCS_FILES))
# ============================== #

# ========== Objects =========== #
OBJS_PATH		:= objs/
NM_OBJS_PATH	:= objs/nm/
OTOOL_OBJS_PATH	:= objs/otool/
NM_OBJS			:= $(addprefix $(NM_OBJS_PATH), $(NM_SRCS_FILES:.c=.o))
OTOOL_OBJS 		:= $(addprefix $(OTOOL_OBJS_PATH), $(OTOOL_SRCS_FILES:.c=.o))
# ============================== #

# ========== Includes ========== #
INCLUDES_PATH	:= includes/
INCLUDES		:= -I $(INCLUDES_PATH)
NM_HEADERS		:= $(addprefix $(INCLUDES_PATH), $(NM_HEADERS_FILES))
OTOOL_HEADERS	:= $(addprefix $(INCLUDES_PATH), $(OTOOL_HEADERS_FILES))
# ============================== #

.PHONY: all clean fclean re

all: $(NM) $(OTOOL)

$(NM_OBJS_PATH)%.o: $(NM_PATH)%.c $(NM_HEADERS)
	@mkdir $(OBJS_PATH) 2> /dev/null || true
	@mkdir $(NM_OBJS_PATH) 2> /dev/null || true
	$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

$(OTOOL_OBJS_PATH)%.o: $(OTOOL_PATH)%.c $(OTOOL_HEADERS)
	@mkdir $(OBJS_PATH) 2> /dev/null || true
	@mkdir $(OTOOL_OBJS_PATH) 2> /dev/null || true
	$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

$(NM): $(NM_OBJS)
	$(CC) $(FLAGS) $(NM_OBJS) -o $@

$(OTOOL): $(OTOOL_OBJS)
	$(CC) $(FLAGS) $(OTOOL_OBJS) -o $@

clean:
	@rm -fv $(NM_OBJS) $(OTOOL_OBJS)
	@rmdir $(OBJS_PATH) 2> /dev/null || true

fclean: clean
	@rm -fv $(NM) $(OTOOL)

re: fclean all
