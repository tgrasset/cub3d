/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrasset <tgrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:32:47 by tgrasset          #+#    #+#             */
/*   Updated: 2023/04/04 15:03:20 by tgrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	check_around_door(t_map *map, int i, int j)
{
	if (map->grid[i][j + 1] == '1' && map->grid[i][j - 1] == '1')
	{
		if (map->grid[i + 1][j] == '1' || map->grid[i - 1][j] == '1'
			|| map->grid[i + 1][j] == '3' || map->grid[i - 1][j] == '3')
			parse_error(8, map);
	}
	else if (map->grid[i + 1][j] == '1' && map->grid[i - 1][j] == '1')
	{
		if (map->grid[i][j + 1] == '1' || map->grid[i][j - 1] == '1'
			|| map->grid[i][j + 1] == '3' || map->grid[i][j - 1] == '3')
			parse_error(8, map);
	}
	else
		parse_error(8, map);
}

void	door_check(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->grid[i] != NULL)
	{
		j = 0;
		while (map->grid[i][j] != '\0')
		{
			if (map->grid[i][j] == '3')
				check_around_door(map, i, j);
			j++;
		}
		i++;
	}
}
