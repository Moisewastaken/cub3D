#include "cub3d.h"

void	pxl_put(mlx_image_t *img, int x, int y, int color)
{
	if (x < 0 || (unsigned int)x >= img->width
		|| y < 0 || (unsigned int)y >= img->height)
		return ;
	((unsigned int *)(img->pixels))[x + y * img->width] = color;
}
