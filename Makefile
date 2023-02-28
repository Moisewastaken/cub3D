# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcochin <mcochin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/02 13:54:33 by mcochin           #+#    #+#              #
#    Updated: 2023/02/27 17:07:42 by mcochin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRCS = src/main.c \
		src/vectors.c \
		src/image.c \
		src/loop.c \
		src/draw.c
OBJS = $(SRCS:.c=.o)

LIBFT = libft
LIBFTPATH = libft/libft.a
MLX = mlx
MLXPATH = mlx/libmlx42.a

CC = gcc
INC = -Iinclude -Imlx/include/MLX42
CFLAGS = -Werror -Wall -Wextra -g
MLXFLAGS = -ldl -lglfw -pthread -lm -Lmlx -lmlx42
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
	@$(RM) $(OBJS) fractol.so
	@$(RM) $(OBJSB) fractol_bonus.so
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