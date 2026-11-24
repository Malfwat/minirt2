# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: me <me@student.42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/10/23 19:49:09 by me                #+#    #+#              #
#    Updated: 2026/11/24 23:18:20 by me               ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	miniRT

NAME_BONUS	=	miniRT_bonus

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror -MMD -MP  -g 

MLX		=	lmlx_Linux

HEADER	=	includes minilibx-linux

SRC_DIR	=	srcs/

SRCS	=	string/ft_strcmp.c \
			string/ft_strlen.c \
			string/ft_memcpy.c \
			string/ft_strdup.c \
			string/ft_strchr.c \
			string/ft_putstr.c \
			string/ft_bzero.c  \
			string/ft_atoi.c   \
			string/ft_atof.c   \
			string/is_wspace.c

SRCS	+=	parsing/open_scene.c\
			parsing/parse.c		\
			parsing/parse_light.c		\
			parsing/double.c	\
			parsing/cam.c		\
			parsing/obj.c		\
			parsing/parse_cy.c	\
			parsing/parse_pl.c	\
			parsing/parse_sp.c	\
			parsing/getter.c	\
			parsing/getter_utils.c	\
			parsing/parse_utils.c		\
			parsing/pass.c		\
			parsing/vector.c	\
			parsing/parse_color.c

SRCS	+=	vector/norme.c vector/operation.c

SRCS	+=	rendering/put_pxl.c	rendering/shading.c\
			rendering/display_utils.c	\
			rendering/color_ops.c	\
			rendering/quadratic.c	\
			rendering/anti_aliasing.c rendering/quadrant_diff.c \
			rendering/system.c rendering/render_utils.c

SRCS	+=	error/rt_error.c

SRCS	+=	gnl/gnl.c gnl/gnl_utils.c

SRCS	+=	obj/obj_utils.c obj/render_sp.c obj/render_cy.c obj/render_pl.c


MANDATORY	=	parsing/loop.c			\
				parsing/parse_line.c	\
				rendering/rt_mlx_loop.c	\
				rendering/get_final_color.c	\
				main.c

BONUS		=	parsing/loop_bonus.c		\
				parsing/parse_co_bonus.c	\
				parsing/obj_bonus.c	\
				parsing/parse_line_bonus.c	\
				rendering/checker_bonus.c	\
				rendering/cy_checker_bonus.c	\
				rendering/render_bonus.c	\
				obj/render_co_bonus.c	\
				rendering/thread_bonus.c	\
				rendering/rt_mlx_loop_bonus.c\
				rendering/get_final_color_bonus.c	\
				rendering/sem_utils_bonus.c\
				main_bonus.c

BUILD	=	.build/

OBJ		=	$(addprefix $(BUILD), $(SRCS:.c=.o))

DEPS	=	$(OBJ:.o=.d)
DEPS	+=	$(addprefix $(BUILD), $(BONUS:.c=.d))
DEPS	+=	$(addprefix $(BUILD), $(MANDATORY:.c=.d))

NB_PC	=	$(shell nproc)

all: minilibx-linux/libmlx_Linux.a $(NAME)

minilibx-linux/libmlx_Linux.a:
	make -C minilibx-linux

bonus: $(NAME_BONUS)

test:
	@bash tests/run_tests.sh

$(NAME):	$(OBJ) $(addprefix $(BUILD), $(MANDATORY:.c=.o)) | minilibx-linux/libmlx_Linux.a
	$(CC) $^ -o $@ -$(MLX) -lXext -lX11 -lm -lz -O3 -L minilibx-linux/

$(NAME_BONUS):	$(OBJ) $(addprefix $(BUILD), $(BONUS:.c=.o)) | minilibx-linux/libmlx_Linux.a
	$(CC) $^ -o $@ -$(MLX) -lXext -lX11 -lm -lz -O3 -pthread -L minilibx-linux/

$(BUILD)%.o:	$(SRC_DIR)%.c Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(addprefix -I, $(HEADER))

clean:
	rm -rf $(BUILD)
	make clean -C minilibx-linux

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all 

.PHONY: all re clean fclean bonus test

-include $(DEPS)