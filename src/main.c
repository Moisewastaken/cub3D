#include "cub3d.h"

void	init_all(t_main *main)
{
	main->player = new_ray(-1, 0, 8, 8);
	main->camera_plane = new_vec(0, 0.66);
	main->scrn_x = 500;
	main->scrn_y = 500;
	main->mlx = mlx_init(main->scrn_x, main->scrn_y, "cub3D", true);
	main->img = mlx_new_image(main->mlx, main->scrn_x, main->scrn_y);
}

int	main(void)
{
	t_main	main;

	init_all(&main);
	mlx_loop_hook(main.mlx, game_loop, &main);
	mlx_loop(main.mlx);
	// game_exit();
}