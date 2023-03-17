/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcochin <mcochin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:58:27 by twinters          #+#    #+#             */
/*   Updated: 2023/03/09 17:28:34 by mcochin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_nb_lines_fd(char *file_name)
{
	int		nb_lines;
	char	*str;
	int		fd;

	fd = open(file_name, O_RDONLY);
	if (fd <= -1)
		return (-1);
	nb_lines = 0;
	str = get_next_line(fd);
	while (str)
	{
		nb_lines++;
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	close (fd);
	return (nb_lines + 1);
}

void	remove_back_n(char **array)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
		{
			if (array[i][j] == '\n')
				array[i][j] = '\0';
			j++;
		}
		i++;
	}
}

char	**get_file_content(char *file_name)
{
	int		i;
	int		fd;
	int		nb_lines;
	char	*str;
	char	**file_content;

	i = 1;
	nb_lines = get_nb_lines_fd(file_name);
	if (nb_lines <= 0)
		return (NULL);
	file_content = malloc(sizeof(char *) * nb_lines);
	if (!file_content)
		return (NULL);
	fd = open(file_name, O_RDONLY);
	str = get_next_line(fd);
	file_content[0] = str;
	while (str)
	{
		str = get_next_line(fd);
		file_content[i] = str;
		i++;
	}
	file_content[i - 1] = NULL;
	remove_back_n(file_content);
	return (file_content);
}
