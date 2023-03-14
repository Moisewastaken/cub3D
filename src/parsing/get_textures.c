/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcochin <mcochin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:30:30 by twinters          #+#    #+#             */
/*   Updated: 2023/03/14 14:28:42 by mcochin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static mlx_image_t	*path_to_texture(mlx_t *mlx, char *path)
{
	mlx_texture_t	*tmp_text;
	mlx_image_t		*new_text;

	if (!path)
		return (NULL);
	tmp_text = mlx_load_png(path);
	new_text = mlx_texture_to_image(mlx, tmp_text);
	mlx_delete_texture(tmp_text);
	if (path)
		free(path);
	return (new_text);
}

static char	*find_element(char **file, char *element)
{
	int		i;
	int		whitespaces;
	char	*path;

	i = 0;
	whitespaces = 3;
	while (file[i] && ft_strncmp(file[i], element, ft_strlen(element)))
		i++;
	if (file[i])
	{
		while (*(file[i] + whitespaces) == ' ')
			whitespaces++;
		path = ft_strdup(file[i] + whitespaces);
	}
	else
		return (NULL);
	i = 0;
	while (path[i])
	{
		if (path[i] == '\n')
			path[i] = '\0';
		i++;
	}
	return (path);
}

static int	find_color(char **file, char *element)
{
	int		i;
	int		color;
	char	**color_array;

	i = 0;
	while (file[i] && ft_strncmp(file[i], element, ft_strlen(element)))
		i++;
	if (file[i])
		color_array = ft_split(file[i] + 2, ',');
	else
		return (0);
	color = 255 << 24 | ft_atoi(color_array[1]) << 8
		| ft_atoi(color_array[2]) << 16 | ft_atoi(color_array[0]);
	free_double_array(color_array);
	return (color);
}

bool	get_texture(char **file, t_texture *texture)
{
	texture->north = path_to_texture(texture->mlx, find_element(file, "NO "));
	texture->south = path_to_texture(texture->mlx, find_element(file, "SO "));
	texture->west = path_to_texture(texture->mlx, find_element(file, "WE "));
	texture->east = path_to_texture(texture->mlx, find_element(file, "EA "));
	if (!texture->north || !texture->west || !texture->east || !texture->south)
		return (false);
	texture->ceiling = find_color(file, "C ");
	texture->floor = find_color(file, "F ");
	return (true);
}
