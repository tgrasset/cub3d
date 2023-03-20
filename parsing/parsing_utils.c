/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrasset <tgrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:30:27 by tgrasset          #+#    #+#             */
/*   Updated: 2023/03/20 11:22:50 by tgrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	skip_spaces(char *str, int i)
{
	while (str[i] != '\0' && str[i] == ' ')
		i++;
	return (i);
}

int	check_rgb_lines(char **tab, int i, t_map *map)
{
	int	j;
	int	res;

	res = 0;
	while (i < map->grid_start)
	{
		j = 0;
		if (ft_strchr(tab[i], 'F') != NULL || ft_strchr(tab[i], 'C') != NULL)
		{
			j = skip_spaces(tab[i], j);
			if ((tab[i][j] == 'F' || tab[i][j] == 'C') && tab[i][j + 1] == ' ')
				res++;
		}
		i++;
	}
	return (res);
}

void	useless_lines_check(char **content, t_map *map, int i)
{
	int	info;
	int	lines;

	info = 0;
	lines = 0;
	if (map->north != NULL)
		info++;
	if (map->south != NULL)
		info++;
	if (map->east != NULL)
		info++;
	if (map->west != NULL)
		info++;
	info = info + check_rgb_lines(content, 0, map);
	while (i < map->grid_start)
	{
		if (content[i][0] != '\0')
			lines++ ;
		i++ ;
	}
	if (lines != info)
		parse_error(4, map);
}
