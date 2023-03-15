# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgrasset <tgrasset@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 11:58:12 by tgrasset          #+#    #+#              #
#    Updated: 2023/03/15 17:48:04 by tgrasset         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
########### VARIABLES

SRCS	=	./parsing/parse_cub_file.c \
			./parsing/parse_error.c \
			./parsing/char_check_texture_paths.c \
			./parsing/extract_content.c \
			./parsing/get_rgb.c \
				
OBJS	=	$(SRCS:%.c=%.o)

NAME	=	cub3D

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror -g

MLX_A	=	./minilibx-linux/libmlx_Linux.a

LIBFT_A	=	./libft/libft.a

###############################################################################
########### RULES

all:		$(NAME)

$(NAME):	$(OBJS) $(MLX_A) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJS) ./libft/libft.a -Lminilibx-linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)

$(MLX_A):
	make -C ./minilibx-linux

$(LIBFT_A):
	make -C ./libft

clean:
	make fclean -C ./libft
	make clean -C ./minilibx-linux
	rm -f $(OBJS)

fclean:		clean
	rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re