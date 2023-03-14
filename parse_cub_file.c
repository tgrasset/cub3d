/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrasset <tgrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:50:12 by tgrasset          #+#    #+#             */
/*   Updated: 2023/03/14 18:26:04 by tgrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    init_map_structure(t_map *map)
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
}

int is_valid_extension(char *path)
{
    int i;

    i = 0;
    while (path[i] != '\0')
		i++;
	i--;
	if (ft_strlen(path) < 5 || path[i] != 'b' || path[i - 1] != 'u'
		|| path[i - 2] != 'c' || path[i - 3] != '.' || path[i - 4] == '/')
		return (0);
	return (1);
}

void    transfer_content_to_struct(char *path, char **content, int height, t_map *map)
{
    int i;
    int fd;

    i = 0;
    content = malloc(sizeof(char *) * (height + 1));
    if (content == NULL)
        parse_error(5, map);
    fd = open(path, O_RDONLY);
    if (fd < 0)
        parse_error(3, map);
    while (i < height)
    {
        content[i] = get_next_line(fd);
        if (content[i] == NULL)
            parse_error(5, map);
        i++;
    }
    content[i] = get_next_line(fd);
    close(fd);
}

void    clean_new_lines(char **content)
{
    int	i;
	int	j;

	i = 0;
	while (content[i] != NULL)
	{
		j = 0;
		while (content[i][j] != '\0')
			j++;
        if (j != 0)
		    j--;
		if (content[i][j] == '\n')
			content[i][j] = '\0';
		i++;
	}
}

void    extract_cub_file_content(char *path, char **content, t_map *map)
{
    int     fd;
    int     height;
    char    *line;

    height = 0;
    fd = open(path, O_RDONLY);
    if (fd < 0)
        parse_error(3, map);
    line = get_next_line(fd);
    if (line == NULL)
        parse_error(5, map);
    while (line != NULL)
    {
        free(line);
        height++;
        line = get_next_line(fd);
    }
    close(fd);
    transfer_content_to_struct(path, content, height, map);
    clean_new_lines(content);
}

int grid_first_line(char **content)
{
    int i;
    int j;

    i = 0;
    while (content[i] != NULL)
    {
        j = 0;
        while (content[i][j] != '\0' && (content[i][j] == ' ' || content[i][j] == '1'))
            j++;
        if (j != 0 && content[i][j] == '\0')
            return (i);
        i++;
    }
    return (-1);
}

void    grid_char_check(char **content, t_map *map, int i, int j)
{
    int player;

    map->grid_start = grid_first_line(content);
    if (map->grid_start < 0)
        parse_error(4, map);
    i = map->grid_start;
    player = 0;
    while (content[i] != NULL)
    {
        j = 0;
        while (content[i][j] != '\0' && (content[i][j] == ' ' || content[i][j] == '1'
            || content[i][j] == '0' || content[i][j] == 'N' || content[i][j] == 'S'
            || content[i][j] == 'W' || content[i][j] == 'E'))
        {
            if (content[i][j] == 'N' || content[i][j] == 'S' || content[i][j] == 'E'
                || content[i][j] == 'W')
                player++;
            j++;
        }
        if (content[i][j] != '\0' || content[i][0] == '\0')
            parse_error(4, map);
        i++;
    }
    if (player != 1)
        parse_error(4, map);
}

char    *copy_texture_path(char *str, t_map *map, int i, char *res)
{
    while (str[i] != '\0' && str[i] != ' ')
        i++;
    res = malloc(sizeof(char) * (i + 1));
    if (res == NULL)
        parse_error(5, map);
    if (str[i] == ' ')
    {
        while (str[i] == ' ')
            i++;
        if (str[i] != '\0')
        {
            free(res);
            parse_error(4, map);
        }
    }
    i = 0;
    while (str[i] != '\0' && str[i] != ' ')
    {
        res[i] = str[i];
        i++;
    }
    res[i] = '\0';
    return (res);
}

char    *get_texture_path(char **content, char *dir, int i, t_map *map)
{
    int j;
    
    j = 0;
    while (content[i] != NULL)
    {
        if (ft_strnstr(content[i], dir, ft_strlen(content[i])) != NULL)
            break;
        i++;
    }
    if (content[i] == NULL)
        return (NULL);
    while (content[i][j] == ' ')
        j++;
    if (content[i][j] != dir[0] || content[i][j + 1] != dir[1] || content[i][j + 2] != ' ')
        parse_error(4, map);
    j = j + 2;
    while (content[i][j] == ' ')
        j++;
    if (content[i][j] != '\0')
        return (copy_texture_path(&content[i][j], map, 0, NULL));
    return (NULL);
}

void    assign_struct_values(t_map *map)
{
    map->north = get_texture_path(map->content, "NO", 0, map);
    map->south = get_texture_path(map->content, "SO", 0, map);
    map->east = get_texture_path(map->content, "EA", 0, map);
    map->west = get_texture_path(map->content, "WE", 0, map);
    // TO BE CONTINUED...
    // get_colour(map->content, map, 'F');
    // get_colour(map->content, map, 'C');
    // get_map_grid(map->content, map);
}

void    parse_cub_file(int ac, char *path, t_map *map)
{
    init_map_structure(map);
    if (ac != 2)
        parse_error(1, map);
    if (is_valid_extension(path) == 0)
        parse_error(2, map);
    extract_cub_file_content(path, map->content, map);
    grid_char_check(map->content, map, 0, 0);
    assign_struct_values(map);
    // TO BE CONTINUED
    // closed_map_check(map->grid, map, 0, 0);
}