# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: me <me@student.42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/10/23 19:49:09 by me                #+#    #+#              #
#    Updated: 2026/11/14 10:52:34 by me               ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	miniRT

NAME_BONUS	=	miniRT_bonus

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror -MMD -MP



MLX		=	lmlx_Linux



HEADER	=	includes minilibx-linux

SRC_DIR	=	srcs/

SRCS	=	main.c

SRCS	+=	string/ft_strcmp.c \
			string/ft_strlen.c \
			string/ft_memcpy.c \
			string/ft_strdup.c \
			string/ft_strchr.c \
			string/ft_bzero.c  \
			string/ft_atoi.c   \
			string/ft_atof.c   \
			string/is_wspace.c

SRCS	+=	parsing/open_scene.c\
			parsing/parse.c		\
			parsing/light.c		\
			parsing/double.c	\
			parsing/cam.c		\
			parsing/obj.c		\
			parsing/cy.c		\
			parsing/pl.c		\
			parsing/sp.c		\
			parsing/getter.c	\
			parsing/getter_utils.c	\
			parsing/utils.c		\
			parsing/pass.c		\
			parsing/vector.c	\
			parsing/color.c

MANDATORY	=	parsing/loop.c	\
				parsing/parse_line.c

BONUS		=	parsing/loop_bonus.c	\
				parsing/parse_line_bonus.c

SRCS	+=	error/rt_error.c

SRCS	+=	gnl/gnl.c gnl/gnl_utils.c

SRCS	+=	light/light.c

SRCS	+=	obj/obj_utils.c

BUILD	=	.build/

OBJ		=	$(addprefix $(BUILD), $(SRCS:.c=.o))

DEPS	=	$(OBJ:.o=.d)

all: minilibx-linux/$(MLX) $(NAME)

minilibx-linux/$(MLX):
	make -C minilibx-linux

bonus: $(NAME_BONUS)

$(NAME):	$(OBJ) $(addprefix $(BUILD), $(MANDATORY:.c=.o))
	$(CC) $^ -o $@ -$(MLX) -lXext -lX11 -lm -lz -O3 -L minilibx-linux/

$(NAME_BONUS):	$(OBJ) $(addprefix $(BUILD), $(BONUS:.c=.o))
	$(CC) $^ -o $@ -$(MLX) -L minilibx-linux/

$(BUILD)%.o:	$(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(addprefix -I, $(HEADER))

clean:
	rm -rf $(BUILD)
	make clean -C minilibx-linux

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all 

.PHONY: all re clean fclean bonus

-include $(DEPS)