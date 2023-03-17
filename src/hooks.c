/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcochin <mcochin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:44:27 by mcochin           #+#    #+#             */
/*   Updated: 2023/03/15 18:44:27 by mcochin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_dir(t_main *main, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = main->player.dir.x;
	main->player.dir.x = main->player.dir.x * cos(rot_speed)
		- main->player.dir.y * sin(rot_speed);
	main->player.dir.y = old_dir_x * sin(rot_speed)
		+ main->player.dir.y * cos(rot_speed);
	old_plane_x = main->cam_plane.x;
	main->cam_plane.x = main->cam_plane.x * cos(rot_speed)
		- main->cam_plane.y * sin(rot_speed);
	main->cam_plane.y = old_plane_x * sin(rot_speed)
		+ main->cam_plane.y * cos(rot_speed);
}

static void	move_player(t_main *main, double dir_x, double dir_y)
{
	double	speed;
	t_point	hit;

	speed = 0.07;
	hit.x = dir_x * 4.0;
	hit.y = dir_y * 4.0;
	if (mlx_is_key_down(main->mlx, MLX_KEY_LEFT_SHIFT))
		speed *= 2;
	if (main->map[(int)main->player.pos.y]
		[(int)(main->player.pos.x + hit.x * speed)] == '0')
		main->player.pos.x += dir_x * speed;
	if (main->map[(int)(main->player.pos.y + hit.y * speed)]
		[(int)(main->player.pos.x)] == '0')
		main->player.pos.y += dir_y * speed;
}

void	key_hooks(t_main *main)
{
	if (mlx_is_key_down(main->mlx, MLX_KEY_W))
		move_player(main, main->player.dir.x, main->player.dir.y);
	if (mlx_is_key_down(main->mlx, MLX_KEY_S))
		move_player(main, -main->player.dir.x, -main->player.dir.y);
	if (mlx_is_key_down(main->mlx, MLX_KEY_A))
		move_player(main, -main->cam_plane.x, -main->cam_plane.y);
	if (mlx_is_key_down(main->mlx, MLX_KEY_D))
		move_player(main, main->cam_plane.x, main->cam_plane.y);
	if (mlx_is_key_down(main->mlx, MLX_KEY_LEFT))
		rotate_dir(main, -0.03);
	if (mlx_is_key_down(main->mlx, MLX_KEY_RIGHT))
		rotate_dir(main, 0.03);
	if (mlx_is_key_down(main->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(main->mlx);
}
