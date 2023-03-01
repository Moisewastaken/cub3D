#include "cub3d.h"

void	draw_player(t_main *main)
{
	int	i;
	int	j;
	int	cell_size;

	cell_size = main->scrn_x / 24;
	i = (int)main->player.pos.x * cell_size - 8;
	while (i < (int)main->player.pos.x * cell_size + 8)
	{
		j = (int)main->player.pos.y * cell_size - 8;
		while (j < (int)main->player.pos.y * cell_size + 8)
		{
			pxl_put(main->img, i, j, 0xFF0000FF);
			j++;
		}
		i++;
	}
}

void draw_line(t_main *main, t_int_point start, t_int_point end)
{
	int dx;
	int dy;

	int	i;
	float	x;
	float	incx;
	float	y;	
	float	incy;
	int		steps;

	i = 0;
	dx = end.x - start.x;
	dy = end.y - start.y;
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	x = start.x;
	y = start.y;
	incx = dx / (float)steps;
	incy = dy / (float)steps;
	while (i <= steps)
	{
		pxl_put(main->img, x, y, 0xFFFF00FF);
		x += incx;
		y += incy;
		i++;
	}
}