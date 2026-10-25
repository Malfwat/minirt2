# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: admoufle <admoufle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/10/23 19:49:09 by me                #+#    #+#              #
#    Updated: 2026/10/25 15:40:33 by admoufle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	miniRT

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror -MMD -MP

HEADER	=	includes

SRC_DIR	=	srcs/

SRCS	=	main.c

SRCS	+=	string/ft_strcmp.c \
			string/ft_strlen.c \
			string/ft_memcpy.c \
			string/ft_strdup.c \
			string/ft_strchr.c	\
			string/ft_atoi.c

SRCS	+=	parsing/open_and_read.c

SRCS	+=	gnl/gnl.c gnl/gnl_utils.c

BUILD	=	.build/

OBJ		=	$(addprefix $(BUILD), $(SRCS:.c=.o))

DEPS	=	$(OBJ:.o=.d)

all: $(NAME)

$(NAME):	$(OBJ)
	$(CC) $(OBJ) -o $@ 

$(BUILD)%.o:	$(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

clean:
	rm -rf $(BUILD)

fclean: clean
	rm -f $(NAME)

re: fclean all 

.PHONY: all re clean fclean

-include $(DEPS)