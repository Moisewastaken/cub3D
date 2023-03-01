#include "cub3d.h"

t_point	new_point(double x, double y)
{
	t_point	new_point;

	new_point.x = x;
	new_point.y = y;
	return (new_point);
}

t_vec	new_vec(t_point pos, t_point dir)
{
	t_vec	new_vec;

	new_vec.dir = new_point(dir.x, dir.y);
	new_vec.pos = new_point(pos.x, pos.y);
	return (new_vec);
}

t_int_point	new_int_point(int	x, int y)
{
	t_int_point	new;

	new.x = x;
	new.y = y;
	return (new);
}

void	rotate_dir(t_main *main, double rot_speed)
{
	double old_dir_x;

	old_dir_x = main->player.dir.x;
	main->player.dir.x = main->player.dir.x * cos(rot_speed) - main->player.dir.y * sin(rot_speed);
	main->player.dir.y = old_dir_x * sin(rot_speed) + main->player.dir.y * cos(rot_speed);
}