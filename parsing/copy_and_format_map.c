/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_and_format_map.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrasset <tgrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 09:58:03 by tgrasset          #+#    #+#             */
/*   Updated: 2023/04/04 11:14:13 by tgrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	fill_rest_with_walls(t_map *map, int i, int j, int side)
{
	while (i < side)
	{
		map->grid[i] = malloc(sizeof(char) * (side + 1));
		if (map->grid[i] == NULL)
			parse_error(5, map);
		j = 0;
		{
			while (j < side)
			{
				map->grid[i][j] = '1';
				j++;
			}
			map->grid[i][j] = '\0';
		}
		i++;
	}
	map->grid[i] = NULL;
}

void	copy_and_fill_line(char *src, char *dest, int i, int side)
{
	while (src[i] != '\0')
	{
		if (src[i] == ' ')
			dest[i] = '1';
		else
			dest[i] = src[i];
		i++;
	}
	while (i < side)
	{
		dest[i] = '1';
		i++;
	}
	dest[i] = '\0';
}

void	copy_map_grid(char **src, t_map *map, int i, int j)
{
	int	side;

	if (map->grid_height > map->grid_width)
		map->grid_width = map->grid_height;
	else if (map->grid_width > map->grid_height)
		map->grid_height = map->grid_width;
	side = map->grid_height;
	map->grid = malloc(sizeof(char *) * (side + 1));
	if (map->grid == NULL)
		parse_error(5, map);
	while (src[i] != NULL)
	{
		map->grid[i] = malloc(sizeof(char) * (side + 1));
		if (map->grid[i] == NULL)
			parse_error(5, map);
		copy_and_fill_line(src[i], map->grid[i], j, side);
		i++;
	}
	if (i < side)
		fill_rest_with_walls(map, i, j, side);
	else
		map->grid[i] = NULL;
}
