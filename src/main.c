#include "cub3d.h"

char	get_player_pos(t_main *main, char **map)
{
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'W'
				|| map[i][j] == 'E' || map[i][j] == 'S')
			{
				main->player.pos.y = (double)i + 0.5;
				main->player.pos.x = (double)j + 0.5;
				return (map[i][j]);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	init_player(t_main *main, char **map)
{
	char	c;

	c = get_player_pos(main, map);
	if (c == 'N')
	{
		main->player.dir = new_point(0.0, -0.50);
		main->cam_plane = new_point(0.66, 0.0);
	}
	if (c == 'S')
	{
		main->player.dir = new_point(0.0, 0.50);
		main->cam_plane = new_point(-0.66, 0.0);
	}
	if (c == 'W')
	{
		main->player.dir = new_point(-0.50, 0.0);
		main->cam_plane = new_point(0.0, -0.66);
	}
	if (c == 'E')
	{
		main->player.dir = new_point(0.50, 0.0);
		main->cam_plane = new_point(0.0, 0.66);
	}
}

void	init_all(t_main *main, char **argv)
{
	main->scrn_x = 1920;
	main->scrn_y = 1080;
	main->mlx = mlx_init(main->scrn_x, main->scrn_y, "cub3D", true);
	main->text.mlx = main->mlx;
	main->map = parsing(&main->text, argv[1]);
	init_player(main, main->map);
	main->map[(int)main->player.pos.y][(int)main->player.pos.x] = '0';
	main->map_size = get_map_size(main->map);
	main->cell_size = main->scrn_x / main->map_size;
	main->img = mlx_new_image(main->mlx, main->scrn_x, main->scrn_y);
	mlx_image_to_window(main->mlx, main->img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_main	main;

	if (argc != 2)
	{
		if (write(2, "Wrong arguments\n", 20))
			return (1);
	}
	init_all(&main, argv);
	mlx_loop_hook(main.mlx, game_loop, &main);
	mlx_loop(main.mlx);
	free_double_array(main.map);
	mlx_terminate(main.mlx);
}
