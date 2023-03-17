/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcochin <mcochin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:44:04 by mcochin           #+#    #+#             */
/*   Updated: 2023/03/15 18:44:05 by mcochin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_pxl_map(t_main *main, int x, int y)
{
	t_int_point	mark;
	t_point		on_map;

	mark.x = x - 100;
	mark.y = y - 100;
	if (((mark.x * mark.x) + (mark.y * mark.y))
		>= 10000)
		return ;
	on_map.x = mark.x / 25.0 + main->player.pos.x;
	on_map.y = mark.y / 25.0 + main->player.pos.y;
	if ((int)on_map.y >= main->map_size.y
		|| (int)on_map.x >= main->map_size.x
		|| (int)on_map.y < 0 || (int)on_map.x < 0
		|| main->map[(int)on_map.y][(int)on_map.x] == ' '
		|| main->map[(int)on_map.y][(int)on_map.x] == '1')
	{
		if (on_map.x - (int)on_map.x > 0.98 || on_map.x - (int)on_map.x < 0.02
			|| on_map.y - (int)on_map.y > 0.98
			|| on_map.y - (int)on_map.y < 0.02)
			pxl_put(main->minimap, x, y, 0xFF000000);
		else
			pxl_put(main->minimap, x, y, 0xFF3b3939);
	}
	else if (main->map[(int)on_map.y][(int)on_map.x] == '0')
		pxl_put(main->minimap, x, y, 0xFFc2c2c2);
}

static t_arrow	init_arrow(t_main *main)
{
	t_arrow	new;

	new.front.x = main->player.dir.x * 20 * 0.6;
	new.front.y = main->player.dir.y * 20 * 0.6;
	new.back.x = -main->player.dir.x * 20 * 0.6;
	new.back.y = -main->player.dir.y * 20 * 0.6;
	new.side.x = (main->player.dir.y * 20 - main->player.dir.x * 30) * 0.6;
	new.side.y = (-main->player.dir.x * 20 - main->player.dir.y * 30) * 0.6;
	new.sym.x = (-main->player.dir.y * 20 - main->player.dir.x * 30) * 0.6;
	new.sym.y = (main->player.dir.x * 20 - main->player.dir.y * 30) * 0.6;
	return (new);
}

static double	area(t_point a, t_point b, t_point c)
{
	return ((a.x * (b.y - c.y) + b.x
			* (c.y - a.y) + c.x * (a.y - b.y)) / 2);
}

static bool	check_pxl_player(t_point a, t_point b, t_point c, t_point point)
{
	if (fabs(area(a, b, c) - fabs(area(b, c, point)) - fabs(area(a, c, point))
			- fabs(area(a, b, point))) < 1e-2)
		return (true);
	return (false);
}

void	draw_map(t_main *main)
{
	int			x;
	int			y;
	t_arrow		player;
	t_point		pxl;

	y = 0;
	player = init_arrow(main);
	while (y < 200)
	{
		x = 0;
		while (x < 200)
		{
			check_pxl_map(main, x, y);
			pxl = new_point((double)x - 100.0, (double)y - 100.0);
			if (check_pxl_player(player.front, player.back, player.side, pxl))
				pxl_put(main->minimap, x, y, 0xFFFF0000);
			if (check_pxl_player(player.front, player.sym, player.back, pxl))
				pxl_put(main->minimap, x, y, 0xFF000000);
			x++;
		}
		y++;
	}
}
