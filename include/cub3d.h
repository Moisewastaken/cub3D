#ifndef CUB3D_H
# define CUB3D_H

#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "MLX42.h"

typedef struct s_vec
{
	double	x;
	double	y;
}t_vec;

typedef struct	s_ray
{
	t_vec	pos;
	t_vec	dir;
}t_ray;

typedef struct	s_pos
{
	int	x;
	int	y;
}t_pos;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		ll;
	int		bpp;
	int		endian;
}t_img;

typedef struct	s_rcast
{
	t_ray	ray;
	t_vec	ray_len;
	t_vec	ray_side;
	t_pos	map_pos;
	t_pos	steps_dir;
	int		side;
}t_rcast;

typedef struct	s_main
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_ray		player;
	t_vec		camera_plane;
	int			scrn_x;
	int			scrn_y;
	int			fov;
	int			map[24][24];
}t_main;


// ----------------------  MAIN.C ----------------------

int		main(void);

// ----------------------  VECTORS.C ----------------------

t_ray	new_ray(double dir_x, double dir_y, double pos_x, double pos_y);
t_vec	new_vec(double x, double y);
t_pos	new_pos(int	x, int y);

// ----------------------  IMAGE.C ----------------------

void	pxl_put(mlx_image_t *img, int x, int y, int color);
void	draw_line(t_main *main, int x, int start, int end, int color);

// ----------------------  LOOP.C ----------------------

void	game_loop(void *arg);

#endif