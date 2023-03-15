/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrasset <tgrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:10:40 by tgrasset          #+#    #+#             */
/*   Updated: 2023/03/15 17:51:49 by tgrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include "./libft/libft.h"

typedef struct  s_map
{
    char            *north;
    char            *south;
    char            *east;
    char            *west;
    unsigned char   floor[3];
    unsigned char   ceiling[3];
    char            **content;
    int             grid_start;
    char            **grid;
}               t_map;

// parsing functions

void    free_tab(char **tab);
void    free_map(t_map *map);
void    parse_error(int n, t_map *map);
void	parse_cub_file(int ac, char *path, t_map *map);
void	assign_struct_values(t_map *map);
void	get_map_grid(t_map *map);
void	get_colour(char **content, t_map *map, int i, char c);
void	set_default_colour(t_map *map, char c);
void	add_value(char *val, char *str, t_map *map);
void	assign_red_green_values(t_map *map, char c, char *r, char *g);
void	assign_blue_value(t_map *map, char c, char *b);
void	set_rgb_values(t_map *map, char c, char *str, int i);
void	init_map_structure(t_map *map);
int     is_valid_extension(char *path);
void	transfer_content_to_struct(char *path, int height, t_map *map);
void	clean_new_lines(t_map *map);
void	extract_cub_file_content(char *path, t_map *map);
int     grid_first_line(char **content);
void	grid_char_check(char **c, t_map *map, int i, int j);
char	*copy_texture_path(char *str, t_map *map, int i, char *res);
char	*get_texture_path(char **content, char *dir, int i, t_map *map);

#endif