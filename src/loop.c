#include "cub3d.h"

static void	get_line(t_main *main, t_rcast *rcast, int x)
{
	double	to_wall_dist;
	int		line_height;
	int		start_point;
	int		end_point;
	int		color;

	color = 0x615b5b;
	if (rcast->side == 0)
		to_wall_dist = rcast->ray_side.x - rcast->ray_len.x;
	else
		to_wall_dist = rcast->ray_side.y - rcast->ray_len.y;
	line_height = (int)main->scrn_y / to_wall_dist;
	start_point = -line_height / 2 + main->scrn_y / 2;
	if (start_point < 0)
		start_point = 0;
	end_point = line_height / 2 + main->scrn_y / 2;
	if (end_point >= 0)
		end_point = main->scrn_y - 1;
	if (rcast->side > 1)
		color = 0x615b5b / 2;
	draw_line(main, x, start_point, end_point, color);
}

static int	dda_loop(t_rcast *rcast)
{
	int	hit;
	int	side;
	int	map[24][24]=
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	hit = 0;
	while (!hit)
	{
		if (rcast->ray_side.x < rcast->ray_side.y)
		{
			rcast->ray_side.x += rcast->ray_len.x;
			rcast->map_pos.x += rcast->steps_dir.x;
			side = 0;
		}
		else
		{
			rcast->ray_side.y += rcast->ray_len.y;
			rcast->map_pos.y += rcast->steps_dir.y;
			side = 1;
		}
		if (map[rcast->map_pos.x][rcast->map_pos.y])
			hit = 1;
	}
	return (side);
}

static void	get_dir(t_rcast *rcast)
{
	rcast->ray_len = new_vec(fabs(1 / rcast->ray.dir.x), fabs(1 / rcast->ray.dir.y));
	if (rcast->ray.dir.x < 0)
	{
		rcast->steps_dir.x = -1;
		rcast->ray_side.x = (rcast->ray.pos.x - rcast->map_pos.x) * rcast->ray_len.x;
	}
	else
	{
		rcast->steps_dir.x = 1;
		rcast->ray_side.x = (rcast->map_pos.x + 1 - rcast->ray.pos.x) * rcast->ray_len.x;
	}
	if (rcast->ray.dir.y < 0)
	{
		rcast->steps_dir.y = -1;
		rcast->ray_side.y = (rcast->ray.pos.y - rcast->map_pos.y) * rcast->ray_len.y;
	}
	else
	{
		rcast->steps_dir.y = 1;
		rcast->ray_side.y = (rcast->map_pos.y + 1 - rcast->ray.pos.y) * rcast->ray_len.y;
	}
}

static	t_ray	get_new_ray(t_main	*main, int x)
{
	t_ray	new;
	double	camera_x;

	camera_x = 2 * x / main->scrn_x - 1;
	new = new_ray(main->player.dir.x + main->camera_plane.x * camera_x,
	main->player.dir.y + main->camera_plane.y * camera_x,
	main->player.pos.x, main->player.pos.y);
	return (new);
}

void	game_loop(void *arg)
{
	t_main	*main;
	t_rcast	rcast;
	int		x;

	main = (t_main *)arg;
	while (x < main->scrn_x)
	{
		rcast.ray = get_new_ray(main, x);
		rcast.map_pos = new_pos((int)main->player.pos.x, (int)main->player.pos.y);
		get_dir(&rcast);
		rcast.side = dda_loop(&rcast);
		get_line(main, &rcast, x);
		x++;
	}
}