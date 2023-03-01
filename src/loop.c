#include "cub3d.h"

int worldMap[24][24]=
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

static void	draw_wall(t_main *main, int x, int y, int color)
{
	int	i;
	int	j;
	int	cell_size;

	i = 0;
	cell_size = main->scrn_x / 24;
	while (i < cell_size)
	{
		j = 0;
		while (j < cell_size)
		{
			pxl_put(main->img, y * cell_size + i, x * cell_size + j, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_main *main)
{
	int		x;
	int		y;

	x = 0;
	while (x < 24)
	{
		y = 0;
		while (y < 24)
		{
			if (worldMap[x][y])
				draw_wall(main, x, y, 0xFF00FFFF);
			else
				draw_wall(main, x, y, 0); 
			y++;
		}
		x++;
	} 
}

void	key_hooks(t_main *main)
{
	if (mlx_is_key_down(main->mlx, MLX_KEY_LEFT))
		main->player.pos.x -= 0.1;
	if (mlx_is_key_down(main->mlx, MLX_KEY_RIGHT))
		main->player.pos.x += 0.1;
	if (mlx_is_key_down(main->mlx, MLX_KEY_UP))
		main->player.pos.y -= 0.1;
	if (mlx_is_key_down(main->mlx, MLX_KEY_DOWN))
		main->player.pos.y += 0.1;
	if (mlx_is_key_down(main->mlx, MLX_KEY_A))
		rotate_dir(main, -0.01);
	if (mlx_is_key_down(main->mlx, MLX_KEY_D))
		rotate_dir(main, 0.01);
}

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
	double	dist;

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
			dist = ray.side_dist.x;
			ray.side_dist.x += ray.delta_dist.x;
			ray.map_pos.x += ray.steps.x;
		}
		else
		{
			dist = ray.side_dist.y;
			ray.side_dist.y += ray.delta_dist.y;
			ray.map_pos.y += ray.steps.y;
		}
		if (worldMap[ray.map_pos.y][ray.map_pos.x])
			hit = 1;
		pxl_put(main->img, ray.map_pos.x * main->cell_size, ray.map_pos.y * main->cell_size, 0xFFFFFFFF);
	}
	t_int_point intersection;
	intersection =  new_int_point(fabs(ray.vec.pos.x + ray.vec.dir.x * dist), fabs(ray.vec.pos.y + ray.vec.dir.y * dist));
	draw_line(main, new_int_point(main->player.pos.x * main->cell_size, main->player.pos.y * main->cell_size), new_int_point(intersection.x * main->cell_size, intersection.y * main->cell_size));
}

void	game_loop(void *arg)
{
	t_main *main;
	
	main = (t_main *)arg;
	key_hooks(main);
	draw_map(main);
	draw_player(main);
	point_dda(main);
}