/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-youb <ael-youb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:10:40 by tgrasset          #+#    #+#             */
/*   Updated: 2023/03/14 16:38:30 by tgrasset         ###   ########.fr       */
/*   Updated: 2023/03/14 16:06:52 by ael-youb         ###   ########.fr       */
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

# define PI 3.1415926535

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
	float	player_x;
	float	player_y;
	float	player_deltax;
	float	player_deltay;
	float	player_angle;
	int		mapp;
}				t_game;

//minilibx_functions
void	init_mlx(t_game *game);
void	add_to_image(t_game *game);
void	draw_map(t_game *game);
void	draw_player(t_game *game);
void	draw_ray(t_game *game);
void	pixel_put(t_data *data, int x, int y, int color);

//hooks
int		destroy_window(t_game *game);
void	close_program(t_game *game);
int		hook_slide(int keycode, t_game *game);

#endif