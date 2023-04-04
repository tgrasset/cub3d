/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closed_map_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrasset <tgrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:56:50 by tgrasset          #+#    #+#             */
/*   Updated: 2023/04/04 10:25:13 by tgrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	get_player_info(char **grid, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (grid[y] != NULL)
	{
		x = 0;
		while (grid[y][x] != '\0')
		{
			if (grid[y][x] == 'N' || grid[y][x] == 'S'
			|| grid[y][x] == 'W' || grid[y][x] == 'E')
			{
				map->p_dir = grid[y][x];
				grid[y][x] = '0';
				map->p_x = x;
				map->p_y = y;
			}
			x++;
		}
		y++;
	}
}

int	out_of_map(char c)
{
	if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'W' && c != 'E'
		&& c != '2' && c != '3')
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

void	get_sprite_number(char **grid, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	map->sprite_nb = 0;
	while (grid[i] != NULL)
	{
		j = 0;
		while (grid[i][j] != '\0')
		{
			if (grid[i][j] == '2')
				map->sprite_nb++;
			j++;
		}
		i++;
	}
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
	get_player_info(grid, map);
	get_sprite_number(grid, map);
}
