/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrasset <tgrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:10:40 by tgrasset          #+#    #+#             */
/*   Updated: 2023/03/16 13:04:54 by tgrasset         ###   ########.fr       */
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
# include "minilibx-linux/mlx.h"

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

typedef struct s_data {
	void			*img;
	char			*addr;
	int				bpp;
	int				ll;
	int				endian;
}				t_data;

typedef struct s_vars {
	void			*mlx;
	void			*mlx_win;
}				t_vars;

typedef struct	s_game
{
	t_map	*map;
	t_vars	*win;
	t_data	*img;
}				t_game;

//minilibx_functions
void	init_mlx(t_game *game);
void	add_to_image(t_game *game);
void	pixel_put(t_data *data, int x, int y, int color);

//hooks
int		destroy_window(t_game *game);
void	close_program(t_game *game);

// parsing functions

void    free_tab(char **tab);
void    free_map(t_map *map);
void    parse_error(int n, t_map *map);
void	parse_cub_file(int ac, char *path, t_map *map);
void	set_rgb_values(t_map *map, char c, char *str, int i);
void	init_map_structure(t_map *map);
int     is_valid_extension(char *path);
void	extract_cub_file_content(char *path, t_map *map);
void	grid_char_check(char **c, t_map *map, int i, int j);
char	*get_texture_path(char **content, char *dir, int i, t_map *map);
void	closed_map_check(char **grid, t_map *map, int x, int y);
void	default_textures_paths_if_necessary(t_map *map);

#endif