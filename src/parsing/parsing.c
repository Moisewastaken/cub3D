/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcochin <mcochin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:42:17 by twinters          #+#    #+#             */
/*   Updated: 2023/03/14 14:14:38 by mcochin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_double_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	get_map_size(char **map)
{
	int	row;
	int	line;

	row = ft_arrlen(map);
	line = ft_strlen(map[0]);
	if (row > line)
		return (row);
	else
		return (line);
}

char	**parsing(t_texture *texture, char *file_name)
{
	char	**file_content;
	char	**map;

	file_content = get_file_content(file_name);
	map = get_map(file_content);
	if (!get_texture(file_content, texture) || !check_map(map))
	{
		printf("Invalid map file.\n");
		free_double_array(map);
		mlx_terminate(texture->mlx);
		exit(1);
	}
	free_double_array(file_content);
	return (map);
}
