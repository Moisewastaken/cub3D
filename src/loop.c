#include "cub3d.h"


void	game_loop(void *arg)
{
	t_main *main;
	
	main = (t_main *)arg;
	key_hooks(main);
	draw_map(main);
	draw_player(main);
	point_dda(main);
}