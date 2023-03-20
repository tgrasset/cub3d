/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrasset <tgrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:26:24 by tgrasset          #+#    #+#             */
/*   Updated: 2023/03/20 09:47:32 by tgrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_map_structure(t_map *map)
{
	map->grid = NULL;
	map->content = NULL;
	map->north = NULL;
	map->south = NULL;
	map->east = NULL;
	map->west = NULL;
	map->floor[0] = 0;
	map->floor[1] = 0;
	map->floor[2] = 0;
	map->ceiling[0] = 0;
	map->ceiling[1] = 0;
	map->ceiling[2] = 0;
	map->grid_start = 0;
	map->grid_height = 0;
	map->grid_width = 0;
}

int	is_valid_extension(char *path)
{
	int	i;

	i = 0;
	while (path[i] != '\0')
		i++;
	i--;
	if (ft_strlen(path) < 5 || path[i] != 'b' || path[i - 1] != 'u'
		|| path[i - 2] != 'c' || path[i - 3] != '.' || path[i - 4] == '/')
		return (0);
	return (1);
}

void	clean_new_lines(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->content[i] != NULL)
	{
		j = 0;
		while (map->content[i][j] != '\0')
			j++;
		if (j != 0)
			j--;
		if (map->content[i][j] == '\n')
			map->content[i][j] = '\0';
		i++;
	}
}

void	transfer_content_to_struct(char *path, int height, t_map *map)
{
	int	i;
	int	fd;

	i = 0;
	map->content = malloc(sizeof(char *) * (height + 1));
	if (map->content == NULL)
		parse_error(5, map);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		parse_error(3, map);
	while (i < height)
	{
		map->content[i] = get_next_line(fd);
		if (i < height - 2 && map->content[i] == NULL)
		{
			close(fd);
			parse_error(5, map);
		}
		i++;
	}
	map->content[i] = NULL;
	close(fd);
	clean_new_lines(map);
}

void	extract_cub_file_content(char *path, t_map *map)
{
	int		fd;
	int		height;
	char	buff[1];
	int		bytes_read;

	height = 0;
	check_if_directory(path, map, 0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		parse_error(3, map);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buff, 1);
		if (bytes_read == -1)
		{
			close(fd);
			parse_error(3, map);
		}
		if (buff[0] == '\n')
			height++;
	}
	height++;
	close(fd);
	transfer_content_to_struct(path, height, map);
}
