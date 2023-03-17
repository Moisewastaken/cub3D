/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcochin <mcochin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:43:49 by mcochin           #+#    #+#             */
/*   Updated: 2023/03/15 18:43:50 by mcochin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_arrlen(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

static bool	check_cell(char **array, int y, int x)
{
	int	height;
	int	width;

	if (array[y][x] != '1' && array[y][x] != ' ')
	{
		height = ft_arrlen(array) - 1;
		width = ft_strlen(array[0]) - 1;
		if (y == height || x == 0 || array[y + 1][x - 1] == ' ')
			return (false);
		if (y == height || array[y + 1][x] == ' ')
			return (false);
		if (y == height || x == width || array[y + 1][x + 1] == ' ')
			return (false);
		if (x == 0 || array[y][x - 1] == ' ')
			return (false);
		if (x == width || array[y][x + 1] == ' ')
			return (false);
		if (y == 0 || x == 0 || array[y - 1][x - 1] == ' ')
			return (false);
		if (y == 0 || array[y - 1][x] == ' ')
			return (false);
		if (y == 0 || x == width || array[y - 1][x + 1] == ' ')
			return (false);
	}
	return (true);
}

static bool	check_char(char c)
{
	static int	letter = 0;

	if (c == -1)
	{
		if (!letter)
			return (false);
		else
			return (true);
	}
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (!letter)
			letter++;
		else
			return (false);
	}
	else if (c != '1' && c != ' ' && c != '0')
		return (false);
	return (true);
}

bool	check_map(char **array)
{
	int	i;
	int	j;

	i = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
		{
			if (!check_char(array[i][j]) || !check_cell(array, i, j))
				return (false);
			j++;
		}
		i++;
	}
	if (!check_char(-1))
		return (false);
	return (true);
}
