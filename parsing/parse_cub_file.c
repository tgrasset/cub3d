/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrasset <tgrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:50:12 by tgrasset          #+#    #+#             */
/*   Updated: 2023/04/04 11:17:07 by tgrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	set_default_colour(t_map *map, char c)
{
	if (c == 'F')
	{
		map->floor[0] = 41;
		map->floor[1] = 156;
		map->floor[2] = 25;
	}
	else if (c == 'C')
	{
		map->ceiling[0] = 135;
		map->ceiling[1] = 206;
		map->ceiling[2] = 235;
	}
}

void	get_colour(char **content, t_map *map, int i, char c)
{
	int	j;
	int	f;

	f = -1;
	while (content[i] != NULL)
	{
		j = 0;
		if (ft_strchr(content[i], c) != NULL)
		{
			while (content[i][j] == ' ')
				j++;
			if (f < 0 && content[i][j] == c && content[i][j + 1] == ' ')
				f = i ;
			else if (f >= 0 && content[i][j] == c && content[i][j + 1] == ' ')
				parse_error(4, map);
		}
		i++;
	}
	if (f < 0)
		set_default_colour(map, c);
	else
		set_rgb_values(map, c, content[f], 0);
}

void	get_map_grid(t_map *map)
{
	int	i;
	int	j;

	i = map->grid_start;
	while (map->content[i] != NULL)
	{
		j = 0;
		while (map->content[i][j] != '\0')
			j++;
		if (j > map->grid_width)
			map->grid_width = j;
		i++;
	}
	map->grid_height = i - map->grid_start;
	closed_map_check(&map->content[map->grid_start], map, 0, 1);
	copy_map_grid(&map->content[map->grid_start], map, 0, 0);
}

void	assign_struct_values(t_map *map)
{
	get_map_grid(map);
	map->north = get_texture_path(map->content, "NO", 0, map);
	map->south = get_texture_path(map->content, "SO", 0, map);
	map->west = get_texture_path(map->content, "WE", 0, map);
	map->east = get_texture_path(map->content, "EA", 0, map);
	get_colour(map->content, map, 0, 'F');
	get_colour(map->content, map, 0, 'C');
	useless_lines_check(map->content, map, 0);
}

void	parse_cub_file(int ac, char *path, t_map *map)
{
	init_map_structure(map);
	if (ac != 2)
		parse_error(1, map);
	if (is_valid_extension(path) == 0)
		parse_error(2, map);
	extract_cub_file_content(path, map);
	grid_char_check(map->content, map, -1, 0);
	assign_struct_values(map);
	default_textures_paths_if_necessary(map);
	door_check(map);
}
