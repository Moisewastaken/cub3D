/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcochin <mcochin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:20:07 by twinters          #+#    #+#             */
/*   Updated: 2023/03/15 18:45:14 by mcochin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_map_line(char *str)
{
	int	i;
	int	whitespace;

	i = 0;
	whitespace = 0;
	while (str[i])
	{
		if (!(str[i] == '0' || str[i] == '1' || str[i] == 'N'
				|| str[i] == 'S' || str[i] == 'E' || str[i] == 'W'
				|| str[i] == ' '))
			return (false);
		if (str[i] == ' ')
			whitespace++;
		i++;
	}
	if (whitespace == i)
		return (false);
	return (true);
}

static int	maplen(char **file)
{
	int	i;

	i = 0;
	while (file[i + 1])
		i++;
	while (!file[i][0])
		i--;
	return (i + 1);
}

static int	get_longest_line(char **array)
{
	int	i;
	int	line;
	int	longest_line;

	i = 0;
	longest_line = 0;
	while (array[i])
	{
		line = ft_strlen(array[i]);
		if (line > longest_line)
			longest_line = line;
		i++;
	}
	return (longest_line);
}

char	*get_map_line(char *line, int longest_line)
{
	int		line_length;
	char	*tmp;
	char	*new;

	line_length = ft_strlen(line);
	tmp = NULL;
	if (longest_line - line_length != 0)
	{
		tmp = malloc(sizeof(char) * (longest_line - line_length + 1));
		ft_memset(tmp, ' ', longest_line - line_length);
		tmp[longest_line - line_length] = '\0';
		new = ft_strjoin(line, tmp);
		free(tmp);
	}
	else
		new = ft_strdup(line);
	return (new);
}

char	**get_map(char **file_content)
{
	int		i;
	int		j;
	int		nb_lines;
	int		longest_line;
	char	**map;

	i = 0;
	j = 0;
	while (file_content[i] && !is_map_line(file_content[i]))
		i++;
	if (!file_content[i])
		return (NULL);
	nb_lines = maplen(file_content + i);
	longest_line = get_longest_line(file_content + i);
	map = malloc(sizeof(char *) * (nb_lines + 1));
	while (j < nb_lines)
	{
		map[j] = get_map_line(file_content[i + j], longest_line);
		j++;
	}
	map[j] = NULL;
	return (map);
}
