#include "cub3d.h"

void	pxl_put(mlx_image_t *img, int x, int y, int color)
{
	((unsigned int *)(img->pixels))[x + y * img->width] = color;
}

void	draw_line(t_main *main, int x, int start, int end, int color)
{
	int	y;

	y = 0;
	while (y <= start)
	{
		// printf("%d %d\n", start, end);
		// printf("x :%d\ny : %d\n", x, y);
		pxl_put(main->img, x, y, color);
		y++;
	}
	while (y <= end)
	{
		// printf("x :%d\ny : %d\n", x, y);
		pxl_put(main->img, x, y, color);
		y++;
	}
	while (y <= main->scrn_y)
	{
		// printf("x :%d\ny : %d\n", x, y);
		pxl_put(main->img, x, y, color);
		y++;
	}
}