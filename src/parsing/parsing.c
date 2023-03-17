/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcochin <mcochin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:42:17 by twinters          #+#    #+#             */
/*   Updated: 2023/03/15 18:43:25 by mcochin          ###   ########.fr       */
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

int	get_size_max(char **map)
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

static bool	is_dot_cub(char *file_name)
{
	int	len;

	len = ft_strlen(file_name) - 4;
	if (!ft_strncmp(file_name + len, ".cub", 5))
		return (true);
	return (false);
}

static void	quit_program(char *msg, char **arr1, char **arr2, mlx_t *mlx)
{
	printf("Error\n");
	printf("%s.\n", msg);
	if (arr1)
		free_double_array(arr1);
	if (arr2)
		free_double_array(arr2);
	mlx_terminate(mlx);
	exit(1);
}

char	**parsing(t_texture *texture, char *file_name)
{
	char	**file_content;
	char	**map;

	file_content = get_file_content(file_name);
	if (!file_content)
		quit_program("Can't open file", NULL, NULL, texture->mlx);
	if (!is_dot_cub(file_name))
		quit_program("File name must end with \".cub\"", file_content,
			NULL, texture->mlx);
	map = get_map(file_content);
	if (!map || !check_map(map))
		quit_program("Invalid map", file_content, map, texture->mlx);
	if (!get_texture(file_content, texture))
		quit_program("Textures are not correctly set in the file",
			file_content, map, texture->mlx);
	free_double_array(file_content);
	return (map);
}
