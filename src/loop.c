#include "cub3d.h"

void	key_hooks(t_main *main)
{
	if (mlx_is_key_down(main->mlx, MLX_KEY_LEFT))
		main->player.pos.x -= 2;
	if (mlx_is_key_down(main->mlx, MLX_KEY_RIGHT))
		main->player.pos.x += 2;
	if (mlx_is_key_down(main->mlx, MLX_KEY_UP))
		main->player.pos.y -= 2;
	if (mlx_is_key_down(main->mlx, MLX_KEY_DOWN))
		main->player.pos.y += 2;
	if (mlx_is_key_down(main->mlx, MLX_KEY_A))
		rotate_dir(main, -0.1);
	if (mlx_is_key_down(main->mlx, MLX_KEY_D))
		rotate_dir(main, 0.1);
}

void	point_dda(t_main *main)
{
	t_vec		vec;
	t_point		side_dist;
	t_int_point dir_steps;

	vec = new_vec(new_point(main->player.pos.x, main->player.pos.y)
		, new_point(main->player.dir.x, main->player.dir.y));
	get_dir(vec);
}

void	game_loop(void *arg)
{
	t_main *main;
	
	main = (t_main *)arg;
	key_hooks(main);
	draw_map(main);
	draw_player(main);
	point_dda(main);
// 	draw_line(main, new_pos((int)main->player.pos.x, (int)main->player.pos.y)
// 	, new_pos((int)main->player.pos.x + main->player.dir.x * 50, (int)main->player.pos.y + main->player.dir.y * 50));
}