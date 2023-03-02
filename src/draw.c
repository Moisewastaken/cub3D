#include "cub3d.h"

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
			if (main->map[x][y])
				draw_wall(main, x, y, 0xFF00FFFF);
			else
				draw_wall(main, x, y, 0); 
			y++;
		}
		x++;
	} 
}
void	draw_player(t_main *main)
{
	int	i;
	int	j;
	int	cell_size;

	cell_size = main->scrn_x / 24;
	i = (int)(main->player.pos.x * cell_size - 8);
	while (i < (int)(main->player.pos.x * cell_size + 8))
	{
		j = (int)(main->player.pos.y * cell_size - 8);
		while (j < (int)(main->player.pos.y * cell_size + 8))
		{
			pxl_put(main->img, i, j, 0xFF0000FF);
			j++;
		}
		i++;
	}
	draw_line(main, new_int_point(main->player.pos.x, main->player.pos.y)
	, new_int_point(main->player.pos.x + main->player.dir.x * 10, main->player.pos.y + main->player.dir.y * 10)); 
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