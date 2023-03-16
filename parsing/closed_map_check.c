/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closed_map_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrasset <tgrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:56:50 by tgrasset          #+#    #+#             */
/*   Updated: 2023/03/16 11:47:02 by tgrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	out_of_map(char c)
{
	if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'W' && c != 'E')
		return (1);
	return (0);
}

void	check_surroundings(char **grid, t_map *map, int x, int y)
{
	if (x == 0)
		parse_error(6, map);
	if (out_of_map(grid[y][x - 1]) || out_of_map(grid[y - 1][x - 1])
		|| out_of_map(grid[y - 1][x]) || out_of_map(grid[y - 1][x + 1])
		|| out_of_map(grid[y][x + 1]) || out_of_map(grid[y + 1][x + 1])
		|| out_of_map(grid[y + 1][x]) || out_of_map(grid[y + 1][x - 1]))
		parse_error(6, map);
}

void	closed_map_check(char **grid, t_map *map, int x, int y)
{
	while (grid[y + 1] != NULL)
	{
		x = 0;
		while (grid[y][x] != '\0')
		{
			if (grid[y][x] != ' ' && grid[y][x] != '1')
				check_surroundings(grid, map, x, y);
			x++;
		}
		y++;
	}
	x = 0;
	while (grid[y][x] != '\0')
	{
		if (grid[y][x] != ' ' && grid[y][x] != '1')
			parse_error(6, map);
		x++;
	}
}
