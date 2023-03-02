#include "cub3d.h"

void	get_delta(t_ray *ray)
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

void	get_dir(t_main *main, t_ray *ray)
{
	if (ray->vec.dir.x < 0)
	{
		ray->steps.x = -1;
		ray->side_dist.x = (main->player.pos.x - ray->map_pos.x) * ray->delta_dist.x;
	}
	else
	{
		ray->steps.x = 1;
		ray->side_dist.x = (ray->map_pos.x + 1.0 - main->player.pos.x) * ray->delta_dist.x;
	}
	if (ray->vec.dir.y < 0)
	{
		ray->steps.y = -1;
		ray->side_dist.y = (main->player.pos.y - ray->map_pos.y) * ray->delta_dist.y;
	}
	else
	{
		ray->steps.y = 1;
		ray->side_dist.y = (ray->map_pos.y + 1.0 - main->player.pos.y) * ray->delta_dist.y;
	}
}

void	point_dda(t_main *main)
{
	t_ray	ray;
	int		hit;
	int		side;
	t_point	dist;

	hit = 0;
	ray.map_pos = new_int_point((int)main->player.pos.x, (int)main->player.pos.y);
	ray.vec = new_vec(new_point(main->player.pos.x, main->player.pos.y)
		, new_point(main->player.dir.x, main->player.dir.y));
	get_delta(&ray);
	get_dir(main, &ray);
	while (!hit)
	{
		if (ray.side_dist.x < ray.side_dist.y)
		{
			dist.x = ray.side_dist.x;
			ray.side_dist.x += ray.delta_dist.x;
			ray.map_pos.x += ray.steps.x;
			side = 1;
		}
		else
		{
			dist.y = ray.side_dist.y;
			ray.side_dist.y += ray.delta_dist.y;
			ray.map_pos.y += ray.steps.y;
			side = 0;
		}
		if (main->map[ray.map_pos.y][ray.map_pos.x])
			hit = 1;
		pxl_put(main->img, ray.map_pos.x * main->cell_size, ray.map_pos.y * main->cell_size, 0xFFFFFFFF);
	}
	t_point intersection;
	if (side)
	{
		intersection =  new_point(fabs(ray.vec.pos.x + ray.vec.dir.x * dist.x), fabs(ray.vec.pos.y + ray.vec.dir.y * dist.x));
		draw_line(main, new_int_point(main->player.pos.x * main->cell_size, main->player.pos.y * main->cell_size), new_int_point(intersection.x * main->cell_size, intersection.y * main->cell_size));
	}
	else
	{
		intersection =  new_point(fabs(ray.vec.pos.x + ray.vec.dir.x * dist.y), fabs(ray.vec.pos.y + ray.vec.dir.y * dist.y));
		draw_line(main, new_int_point(main->player.pos.x * main->cell_size, main->player.pos.y * main->cell_size), new_int_point(intersection.x * main->cell_size, intersection.y * main->cell_size));

	}
}