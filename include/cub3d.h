#ifndef CUB3D_H
# define CUB3D_H

#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "MLX42.h"

typedef struct	s_point
{
	double	x;
	double	y;
}t_point;

typedef struct	s_int_point
{
	int x;
	int y;
}t_int_point;

typedef struct	s_vec
{
	t_point	pos;
	t_point	dir;
}t_vec;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		ll;
	int		bpp;
	int		endian;
}t_img;

typedef struct	s_ray
{
	t_vec		vec;
	t_int_point map_pos;
	t_int_point steps;
	t_point		side_dist;
	t_point		delta_dist;
}t_ray;

typedef struct	s_main
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_vec		player;
	int			scrn_x;
	int			scrn_y;
	int			cell_size;
}t_main;


// ----------------------  MAIN.C ----------------------

int		main(void);

// ----------------------  VECTORS.C ----------------------

t_vec		new_vec(t_point pos, t_point dir);
t_point		new_point(double x, double y);
t_int_point	new_int_point(int	x, int y);
void		rotate_dir(t_main *main, double rot_speed);

// ----------------------  IMAGE.C ----------------------

void	pxl_put(mlx_image_t *img, int x, int y, int color);

// ----------------------  LOOP.C ----------------------

void	game_loop(void *arg);
void	point_dda(t_main *main);

// ----------------------  DRAW.C ----------------------
void	draw_map(t_main *main);
void	draw_player(t_main *main);
void	draw_line(t_main *main, t_int_point start, t_int_point end);

#endif