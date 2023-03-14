#include "cub3d.h"

static void	draw_wall(t_main *main, int x, int y, int color)
{
	int	i;
	int	j;
	int	cell;

	i = 0;
	cell = main->cell_size / 5;
	while (i < cell)
	{
		j = 0;
		while (j < cell)
		{
			pxl_put(main->img, x * cell + j + 20, y * cell + i + 20, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_main *main)
{
	int		x;
	int		y;

	y = 0;
	while (main->map[y])
	{
		x = 0;
		while (main->map[y][x])
		{
			if (main->map[y][x] && main->map[y][x] == '1')
				draw_wall(main, x, y, 0xFF302f2f);
			else if (main->map[y][x] && main->map[y][x] == '0')
				draw_wall(main, x, y, 0xFFaba9a9);
			x++;
		}
		y++;
	}
}

void	draw_player(t_main *main)
{
	int	i;
	int	j;
	int	cell_size;

	cell_size = main->cell_size / 5;
	i = (int)(main->player.pos.x * cell_size - 2);
	while (i < (int)(main->player.pos.x * cell_size + 2))
	{
		j = (int)(main->player.pos.y * cell_size - 2);
		while (j < (int)(main->player.pos.y * cell_size + 2))
		{
			pxl_put(main->img, i + 20, j + 20, 0xFF000000);
			j++;
		}
		i++;
	}
}
