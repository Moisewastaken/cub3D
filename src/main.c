#include "cub3d.h"

void	init_all(t_main *main)
{
	main->player = new_vec(new_point(360.0, 360.0), new_point(0, 0));
	main->scrn_x = 720;
	main->scrn_y = 720;
	main->mlx = mlx_init(main->scrn_x, main->scrn_y, "cub3D", true);
	main->img = mlx_new_image(main->mlx, main->scrn_x, main->scrn_y);
	mlx_image_to_window(main->mlx, main->img, 0, 0);
}

int	main(void)
{
	t_main	main;

	init_all(&main);
	mlx_loop_hook(main.mlx, game_loop, &main);
	mlx_loop(main.mlx);
	// game_exit();
}