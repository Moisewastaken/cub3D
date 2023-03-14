#include "cub3d.h"

static mlx_image_t	*get_cur_text(t_main *main, t_ray *ray)
{
	if (ray->hit_side && ray->vec.dir.x < 0.0)
		return (main->text.north);
	if (ray->hit_side && ray->vec.dir.x > 0.0)
		return (main->text.east);
	if (!ray->hit_side && ray->vec.dir.y < 0.0)
		return (main->text.south);
	if (!ray->hit_side && ray->vec.dir.y > 0.0)
		return (main->text.west);
	return (NULL);
}

static double	get_hit_point(t_main *main, t_ray *ray, double wall_dist)
{
	double	hit_point;

	if (ray->hit_side)
		hit_point = main->player.pos.y + wall_dist * ray->vec.dir.y;
	else
		hit_point = main->player.pos.x + wall_dist * ray->vec.dir.x;
	hit_point -= floor(hit_point);
	return (hit_point);
}

static t_line	get_line(t_main *main, double wall_dist)
{
	t_line	new_line;

	new_line.height = (int)(main->scrn_y / wall_dist);
	new_line.start = -new_line.height / 2 + main->scrn_y / 2;
	new_line.end = new_line.height / 2 + main->scrn_y / 2;
	if (new_line.end > main->scrn_y)
		new_line.end = main->scrn_y - 1;
	return (new_line);
}

static void	draw_line(t_main *main, t_line line, t_ray *ray, int x)
{
	mlx_image_t	*cur_text;
	int			y;
	int			c_x;
	int			c_y;
	int			c;

	y = -1;
	cur_text = get_cur_text(main, ray);
	while (line.start >= 0 && y++ < line.start)
		pxl_put(main->img, x, y, main->text.ceiling);
	while (y < line.end)
	{
		c_x = (int)(line.hit_point * cur_text->width);
		c_y = (int)((double)(y - line.start)
				/ (double)line.height * cur_text->height);
		c = ((unsigned *)(cur_text->pixels))[c_x + c_y * cur_text->width];
		pxl_put(main->img, x, y, c);
		y++;
	}
	y--;
	while (y++ < main->scrn_y)
		pxl_put(main->img, x, y, main->text.floor);
}

void	render_line(t_main *main, t_ray *ray, int x)
{
	double		wall_dist;
	t_line		line;

	if (ray->hit_side)
		wall_dist = ray->side_dist.x - ray->delta_dist.x;
	else
		wall_dist = ray->side_dist.y - ray->delta_dist.y;
	line = get_line(main, wall_dist);
	line.hit_point = get_hit_point(main, ray, wall_dist);
	draw_line(main, line, ray, x);
}
