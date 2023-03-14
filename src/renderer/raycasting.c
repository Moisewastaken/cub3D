#include "cub3d.h"

static void	get_delta(t_ray *ray)
{
	if (ray->vec.dir.x == 0)
		ray->delta_dist.x = 1e30;
	else
		ray->delta_dist.x = fabs(1 / ray->vec.dir.x);
	if (ray->vec.dir.y == 0)
		ray->delta_dist.y = 1e30;
	else
		ray->delta_dist.y = fabs(1 / ray->vec.dir.y);
}

static void	get_dir(t_main *main, t_ray *ray)
{
	if (ray->vec.dir.x <= 0)
	{
		ray->steps.x = -1;
		ray->side_dist.x = (main->player.pos.x - ray->map_pos.x)
			* ray->delta_dist.x;
	}
	else
	{
		ray->steps.x = 1;
		ray->side_dist.x = (ray->map_pos.x + 1.0 - main->player.pos.x)
			* ray->delta_dist.x;
	}
	if (ray->vec.dir.y <= 0)
	{
		ray->steps.y = -1;
		ray->side_dist.y = (main->player.pos.y - ray->map_pos.y)
			* ray->delta_dist.y;
	}
	else
	{
		ray->steps.y = 1;
		ray->side_dist.y = (ray->map_pos.y + 1.0 - main->player.pos.y)
			* ray->delta_dist.y;
	}
}

static t_ray	get_new_ray(t_main *main, int x)
{
	t_point	ray_dir;
	t_ray	new_ray;
	double	x_cam;

	x_cam = 2 * x / (double)main->scrn_x - 1;
	new_ray.map_pos = new_int_point((int)main->player.pos.x,
			(int)main->player.pos.y);
	ray_dir.x = main->player.dir.x + main->cam_plane.x * x_cam;
	ray_dir.y = main->player.dir.y + main->cam_plane.y * x_cam;
	new_ray.vec = new_vec(new_point(main->player.pos.x,
				main->player.pos.y), ray_dir);
	get_delta(&new_ray);
	get_dir(main, &new_ray);
	new_ray.hit_side = 0;
	return (new_ray);
}

void	point_dda(t_main *main, int x)
{
	t_ray	ray;
	int		hit;

	hit = 0;
	ray = get_new_ray(main, x);
	while (!hit)
	{
		if (ray.side_dist.x < ray.side_dist.y)
		{
			ray.side_dist.x += ray.delta_dist.x;
			ray.map_pos.x += ray.steps.x;
			ray.hit_side = 1;
		}
		else
		{
			ray.side_dist.y += ray.delta_dist.y;
			ray.map_pos.y += ray.steps.y;
			ray.hit_side = 0;
		}
		if (main->map[ray.map_pos.y][ray.map_pos.x] == '1')
			hit = 1;
	}
	render_line(main, &ray, x);
}
