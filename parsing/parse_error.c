/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrasset <tgrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:57:35 by tgrasset          #+#    #+#             */
/*   Updated: 2023/04/04 10:51:57 by tgrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_map(t_map *map)
{
	if (map->north != NULL)
		free(map->north);
	if (map->south != NULL)
		free(map->south);
	if (map->east != NULL)
		free(map->east);
	if (map->west != NULL)
		free(map->west);
	if (map->grid != NULL)
		free_tab(map->grid);
	if (map->content != NULL)
		free_tab(map->content);
}

void	parse_error(int n, t_map *map)
{
	if (n == 1)
		ft_putendl_fd("Error\ncub3D must be executed with map path only", 2);
	else if (n == 2)
		ft_putendl_fd("Error\nMap must be a valid .cub file", 2);
	else if (n == 3)
		ft_putendl_fd("Error\nMap couldn't be read or file doesn't exist", 2);
	else if (n == 4)
		ft_putendl_fd("Error\ncub file content invalid", 2);
	else if (n == 5)
		ft_putendl_fd("Error\nMalloc couldn't allocate memory", 2);
	else if (n == 6)
		ft_putendl_fd("Error\nThe map must be closed with walls", 2);
	else if (n == 7)
		ft_putendl_fd("Error\nThis path leads to a directory", 2);
	else if (n == 8)
		ft_putendl_fd("Error\nWrong door configuration", 2);
	free_map(map);
	exit(1);
}

void	check_if_directory(char *path, t_map *map, int fd)
{
	fd = open(path, O_DIRECTORY);
	if (fd > 0)
	{
		close(fd);
		parse_error(7, map);
	}
}
