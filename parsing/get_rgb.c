/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rgb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrasset <tgrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:30:27 by tgrasset          #+#    #+#             */
/*   Updated: 2023/03/15 17:52:16 by tgrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	set_default_colour(t_map *map, char c)
{
	if (c == 'F')
	{
		map->floor[0] = 124;
		map->floor[1] = 252;
		map->floor[2] = 0;
	}
	else if (c == 'C')
	{
		map->ceiling[0] = 135;
		map->ceiling[1] = 206;
		map->ceiling[2] = 235;
	}
}

void	add_value(char *val, char *str, t_map *map)
{
	int	i;

	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (i > 3 || i == 0)
		parse_error(4, map);
	val[0] = str[0];
	if (i == 1)
		val[1] = '\0';
	else if (i == 2)
	{
		val[1] = str[1];
		val[2] = '\0';
	}
	else
	{
		val[1] = str[1];
		val[2] = str[2];
		val[3] = '\0';
	}
	if (ft_atoi(val) > 255)
		parse_error(4, map);
}

void	assign_red_green_values(t_map *map, char c, char *r, char *g)
{
	if (c == 'F')
	{
		map->floor[0] = ft_atoi(r);
		map->floor[1] = ft_atoi(g);
	}
	else if (c == 'C')
	{
		map->ceiling[0] = ft_atoi(r);
		map->ceiling[1] = ft_atoi(g);
	}
}

void	assign_blue_value(t_map *map, char c, char *b)
{
	if (c == 'F')
		map->floor[2] = ft_atoi(b);
	else if (c == 'C')
		map->ceiling[2] = ft_atoi(b);
}

void	set_rgb_values(t_map *map, char c, char *str, int i)
{
	char	r[4];
	char	g[4];
	char	b[4];

	while (str[i] == ' ')
		i++;
	add_value(r, &str[i], map);
	while (ft_isdigit(str[i]) || str[i] == ' ')
		i++;
	if (str[i] != ',')
		parse_error(4, map);
	i++;
	while (str[i] == ' ')
		i++;
	add_value(g, &str[i], map);
	while (ft_isdigit(str[i]) || str[i] == ' ')
		i++;
	if (str[i] != ',')
		parse_error(4, map);
	i++;
	while (str[i] == ' ')
		i++;
	add_value(b, &str[i], map);
	assign_red_green_values(map, c, r, g);
	assign_blue_value(map, c, b);
}
