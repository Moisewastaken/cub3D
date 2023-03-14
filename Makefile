# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcochin <mcochin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/02 13:54:33 by mcochin           #+#    #+#              #
#    Updated: 2023/03/09 10:54:34 by mcochin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRCS = src/main.c \
		src/hooks.c \
		src/renderer/vectors.c \
		src/renderer/image.c \
		src/renderer/loop.c \
		src/renderer/draw.c \
		src/renderer/raycasting.c \
		src/renderer/texturing.c \
		src/parsing/parsing.c \
		src/parsing/get_file_content.c \
		src/parsing/check_map.c \
		src/parsing/get_map.c \
		src/parsing/get_textures.c
OBJS = $(SRCS:.c=.o)

LIBFT = libft
LIBFTPATH = libft/libft.a
MLX = mlx
MLXPATH = mlx/libmlx42.a

CC = gcc
INC = -Ilibft -Iinclude -Imlx/include/MLX42
CFLAGS = -Werror -Wall -Wextra -g #-Ofast
MLXFLAGS = -ldl -lglfw -pthread -lm -Lmlx #-lmlx42m
RM = rm -f
MAKE = make -C

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFTPATH) $(MLXPATH)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFTPATH) $(MLXPATH) $(MLXFLAGS)

%.o : %.c
	$(CC) -o $@ -c $< $(CFLAGS) $(INC)

$(LIBFTPATH) :
	@$(MAKE) $(LIBFT) 

$(MLXPATH) :
	@$(MAKE) $(MLX) -s

clean :
	@$(RM) $(OBJS)
	@$(RM) $(OBJSB)
	@$(MAKE) $(LIBFT) clean
	@$(MAKE) $(MLX) clean

fclean : clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)/libft.a
	@$(RM) $(MLX)/libmlx.a
	@echo DONE

re : fclean $(NAME)

f : fclean

r : all
	@clear
	@./$(NAME)

.PHONY: all fclean re clean