#ifndef CUB3D_H
# define CUB3D_H

#define	PI	3.14159265359

#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "MLX42.h"
#include "libft.h"

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

typedef struct	s_line
{
	int		start;
	int		end;
	int		height;
	double	hit_point;
}t_line;

typedef struct	s_ray
{
	int			hit_side;
	t_vec		vec;
	t_int_point map_pos;
	t_int_point steps;
	t_point		side_dist;
	t_point		delta_dist;
}t_ray;

typedef struct	s_texture
{
	mlx_t		*mlx;
	mlx_image_t	*south;
	mlx_image_t	*north;
	mlx_image_t	*west;
	mlx_image_t	*east;
	int			floor;
	int			ceiling;
}t_texture;

typedef struct	s_main
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_texture	text;
	t_vec		player;
	t_point		cam_plane;
	char		**map;
	int			scrn_x;
	int			scrn_y;
	int			cell_size;
	int			map_size;
}t_main;

// ----------------------  VECTORS.C ----------------------
t_vec		new_vec(t_point pos, t_point dir);
t_point		new_point(double x, double y);
t_int_point	new_int_point(int	x, int y);

// ----------------------  IMAGE.C ----------------------
void	pxl_put(mlx_image_t *img, int x, int y, int color);
int		get_neg_col(mlx_image_t *img, int x, int y);

// ----------------------  LOOP.C ----------------------
void	game_loop(void *arg);

// ----------------------  RAYCASTING.C ----------------------
void	point_dda(t_main *main, int x);

// ----------------------  DRAW.C ----------------------
void	draw_map(t_main *main);
void	draw_player(t_main *main);
void	plot_line (t_main *main, t_int_point start, t_int_point end);

// ----------------------  HOOKS.C ----------------------
void	key_hooks(t_main *main);
void	rotate_dir(t_main *main, double rot_speed);

// ----------------------  TEXTURING.C ----------------------
void	render_line(t_main *main, t_ray *ray, int x);

// ----------------------  PARSING.C ----------------------
char	**parsing(t_texture *texture, char *file_name);
void	free_double_array(char **array );
int		get_map_size(char **map);
t_vec	get_player_pos_dir(char **map);

// -------------------  GET_FILE_CONTENT.C -------------------
char	**get_file_content(char *file_name);

// -------------------  GET_TEXTURES.C -------------------
bool	get_texture(char **file, t_texture *texture);

// ------------------------  GET_MAP.C ------------------------
char **get_map(char **file_content);
int	ft_arrlen(char **array);
bool	check_map(char **array);

#endif