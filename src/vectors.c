#include "cub3d.h"

t_vec	new_vec(double x, double y)
{
	t_vec	new_vec;

	new_vec.x = x;
	new_vec.y = y;
	return (new_vec);
}

t_ray	new_ray(double dir_x, double dir_y, double pos_x, double pos_y)
{
	t_ray	new_ray;

	new_ray.dir = new_vec(dir_x, dir_y);
	new_ray.pos = new_vec(pos_x, pos_y);
	return (new_ray);
}

t_pos	new_pos(int	x, int y)
{
	t_pos	new;

	new.x = x;
	new.y = y;
	return (new);
}