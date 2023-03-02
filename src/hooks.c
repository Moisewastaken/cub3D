#include "cub3d.h"

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
		rotate_dir(main, -0.1);
	if (mlx_is_key_down(main->mlx, MLX_KEY_D))
		rotate_dir(main, 0.1);
}