/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcochin <mcochin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:44:24 by mcochin           #+#    #+#             */
/*   Updated: 2023/03/15 18:50:07 by mcochin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	new_point(double x, double y)
{
	t_point	new_point;

	new_point.x = x;
	new_point.y = y;
	return (new_point);
}

t_vec	new_vec(t_point pos, t_point dir)
{
	t_vec	new_vec;

	new_vec.pos = new_point(pos.x, pos.y);
	new_vec.dir = new_point(dir.x, dir.y);
	return (new_vec);
}

t_int_point	new_int_point(int x, int y)
{
	t_int_point	new;

	new.x = x;
	new.y = y;
	return (new);
}
