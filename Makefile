# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/14 17:17:38 by jubaldo           #+#    #+#              #
#    Updated: 2024/06/02 17:44:13 by jubaldo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

SRCS		=	events/handle_keypress.c 	\
				events/handle_keyrelease.c  \
				get_next_line/get_next_line.c \
				init/init_game.c \
				init/init_player.c \
				init/init_cub3d.c \
				libft/ft_atoi.c \
				libft/ft_memcpy.c \
				libft/ft_memset.c \
				libft/ft_realloc.c \
				libft/ft_split.c \
				libft/ft_strdup.c \
				libft/ft_strlen.c \
				libft/ft_strncmp.c \
				libft/ft_strcmp.c \
				libft/ft_strchr.c \
				parsing/parse_args.c \
				parsing/parse_color.c \
				parsing/parse_file.c \
				parsing/parse_map.c \
				parsing/parse_texture.c \
				parsing/validate_map_walls.c \
				player/linear_moves.c \
				player/rotation_moves.c \
				player/update_player.c \
				raycasting/calculations.c \
				raycasting/draw.c \
				raycasting/getters.c \
				raycasting/init_ray.c \
				raycasting/perform_dda.c \
				raycasting/perform_raycasting.c \
				utils/check.c \
				utils/exit.c \
				utils/free.c \
				main.c

OBJS_DIR	=	obj

OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror -g3

LFLAGS		=	libmlx.a libmlx_Linux.a -lX11 -lXext -lm

OBJS		=	$(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			make -C minilibx/ && mv minilibx/libmlx.a . && mv minilibx/libmlx_Linux.a .
			$(CC) -o $(NAME) $(OBJS) $(LFLAGS)
			@echo "\033[32m ~~ ./cub3d successfully created! ~~"
			@echo "$$BIBOU"

clean:
			make clean -C minilibx/
			rm -rf $(OBJS)
			@echo "\033[31m ~~ ./cub3d successfully deleted! ~~"
			@echo "$$PQ"
				
fclean:		clean
			rm -rf $(NAME) libmlx.a libmlx_Linux.a
			@echo "\033[31m ~~ ./cub3d successfully fdeleted! ~~"
			@echo "$$PQ"

re:			fclean all

.PHONY:		all clean fclean re


info: bibou
define BIBOU

            _    _____     _ 
  ___ _   _| |__|___ /  __| |
 / __| | | | '_ \ |_ \ / _` |
| (__| |_| | |_) |__) | (_| |
 \___|\__,_|_.__/____/ \__,_|
                             

endef
export BIBOU

info: pq
define PQ

 .--""--.___.._
(  <__>  )     `-.
|`--..--'|      <|      cleaning  ....
|       :|       /
|       :|--""-./
`.__  __;' 
    ""
endef
export PQ
