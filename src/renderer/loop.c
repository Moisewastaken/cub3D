/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcochin <mcochin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:43:36 by mcochin           #+#    #+#             */
/*   Updated: 2023/03/15 18:43:36 by mcochin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_loop(void *arg)
{
	t_main	*main;
	int		x;

	main = (t_main *)arg;
	x = 0;
	key_hooks(main);
	while (x < main->scrn_x)
	{
		point_dda(main, x);
		x++;
	}
	draw_map(main);
}
