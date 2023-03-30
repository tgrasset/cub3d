/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rgb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrasset <tgrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:30:27 by tgrasset          #+#    #+#             */
/*   Updated: 2023/03/29 14:09:57 by tgrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	fill_value_tab(char *val, char *str, int i)
{
	val[0] = str[0];
	if (i == 1)
		val[1] = '\0';
	else if (i == 2)
	{
		val[1] = str[1];
		val[2] = '\0';
	}
	else if (i == 3)
	{
		val[1] = str[1];
		val[2] = str[2];
		val[3] = '\0';
	}
}

void	add_value(char *val, char *str, t_map *map, int end_flag)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] == '0')
		i++;
	if (i != 0 && ft_isdigit(str[i] == 0))
		i--;
	j = i;
	while (ft_isdigit(str[i]))
		i++;
	if (i - j > 3 || i == 0)
		parse_error(4, map);
	fill_value_tab(val, &str[j], i - j);
	if (ft_atoi(val) > 255)
		parse_error(4, map);
	if (end_flag == 1)
	{
		i = 0;
		while (ft_isdigit(str[i]) || str[i] == ' ')
			i++;
		if (str[i] != '\0')
			parse_error(4, map);
	}
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

	i = skip_spaces(str, i);
	i++;
	i = skip_spaces(str, i);
	add_value(r, &str[i], map, 0);
	while (ft_isdigit(str[i]) || str[i] == ' ')
		i++;
	if (str[i] != ',')
		parse_error(4, map);
	i++;
	i = skip_spaces(str, i);
	add_value(g, &str[i], map, 0);
	while (ft_isdigit(str[i]) || str[i] == ' ')
		i++;
	if (str[i] != ',')
		parse_error(4, map);
	i++;
	i = skip_spaces(str, i);
	add_value(b, &str[i], map, 1);
	assign_red_green_values(map, c, r, g);
	assign_blue_value(map, c, b);
}
