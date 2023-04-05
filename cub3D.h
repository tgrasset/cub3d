/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrasset <tgrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:10:40 by tgrasset          #+#    #+#             */
/*   Updated: 2023/04/05 12:43:21 by tgrasset         ###   ########.fr       */
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
# include <X11/keysym.h>
# include <X11/keysymdef.h>

# define PI 3.1415926535
# define P2 1.5707963268
# define P3 4.7123889804
# define DR 0.0174533 // 1 degre = DR radians
# define RAY_NUMBER 1080
# define SCALE_RAY 18
# define HEIGHT 768
# define LOOP 12

typedef struct s_minimap
{
	int			x;
	int			y;
	int			x_origin;
	int			y_origin;
	int			xo;
	int			yo;
	int			pix;
	int			cases;
}				t_minimap;

typedef struct s_map
{
	char			*north;
	char			*south;
	char			*east;
	char			*west;
	unsigned char	floor[3];
	unsigned char	ceiling[3];
	int				floor_int;
	int				ceiling_int;
	char			**content;
	int				grid_height;
	int				grid_width;
	int				grid_start;
	char			**grid;
	int				p_x;
	int				p_y;
	char			p_dir;
	int				sprite_nb;
}				t_map;

typedef struct s_data {
	void			*img;
	char			*addr;
	int				bpp;
	int				ll;
	int				endian;
	int				w;
	int				h;
}				t_data;

typedef struct s_vars {
	void			*mlx;
	void			*mlx_win;
}				t_vars;

typedef struct s_raystorage
{
	int		r;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	int		dof_max;
	int		color;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	dis_h;
	float	hx;
	float	hy;
	float	dis_v;
	float	vx;
	float	vy;
	float	distance;
	int		actual_height;
}				t_raystorage;

typedef struct s_sprites
{
	int		*order;
	float	*dist;
	float	*sp_x;
	float	*sp_y;
	float	rel_x;
	float	rel_y;
	int		height;
}				t_sprites;

typedef struct s_game
{
	t_map			map;
	t_vars			*win;
	t_data			*img;
	t_data			north;
	t_data			south;
	t_data			east;
	t_data			west;
	t_data			sp_1;
	t_data			sp_2;
	t_data			sp_3;
	t_data			sp_4;
	t_data			sp_5;
	t_data			sp_6;
	t_data			door;
	float			player_x;
	float			player_y;
	float			player_deltax;
	float			player_deltay;
	float			player_angle;
	float			strafe_angle;
	float			strafe_deltax;
	float			strafe_deltay;
	float			ray_dist[RAY_NUMBER];
	t_raystorage	store;
	int				scale_ray;
	int				forwd;
	int				backwd;
	int				strafe_l;
	int				strafe_r;
	int				look_l;
	int				look_r;
	int				pix;
	int				sprint_mult;
	int				focus;
	int				frame;
	t_sprites		sprites;
}				t_game;

//main
void	select_player_dir(t_game *game);
void	ceiling_floor_colors(t_game *game);
void	init_game_struct(t_game *game);
void	init_player_struct(t_game *game);

//init_game.c
void	init_mlx(t_game *game);
int		render(t_game *game);
void	draw_three_d(t_game *game, float distance, float ra);
void	loop_draw_three_d(t_game *game, float height, float offset);
void	pixel_put(t_data *data, int x, int y, int color);

//minimap.c
void	draw_player(t_game *game);
void	draw_map(t_game *game);
void	init_minimap(t_minimap *minimap, t_game *game);	
void	load_textures(t_game *game);
void	draw_player(t_game *game);
void	draw_minimap_dot(t_game *game);
void	util_draw_player(t_game *game, int cases, int pix);

//raycasting
void	draw_rays(t_game *game);
void	distance_h(t_game *game);
void	distance_v(t_game *game);
void	loop_distance_v(t_game *game);
void	loop_distance_h(t_game *game);
void	pick_v_or_h(t_game *game);
void	init_draw_ray(t_game *game);
void	reinitialize_distances(t_game *game);
int		rgb(int r, int g, int b);
void	ray_special_case(t_game *game);
float	dist(float ax, float ay, float bx, float by);
int		get_colour_from_texture(int height, t_data *data,
			t_game *game, int wall_y);
void	loop_loop_drawthree_d(t_game *game, float height, float offset, int j);
int		is_wall_or_door(t_game *game);
void	east_west_walls(t_game *game, float height, float offset, int j);

//hooks
int		close_program(t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
void	open_close_door(t_game *game);

//player_move
void	go_backward(t_game *game);
void	go_forward(t_game *game);
void	strafe_left(t_game *game);
void	strafe_right(t_game *game);
void	move_player(t_game *game);

//player_rotate
void	turn_left(t_game *game);
void	turn_right(t_game *game);

//wall_secure
int		check_wallhack(t_game *game);
int		check_wallhack_backward(t_game *game);
int		check_wallhack_strafe_l(t_game *game);
int		check_wallhack_strafe_r(t_game *game);

//wall_secure_right
int		check_angle_righty_s(t_game *game);
int		check_angle_rightx_s(t_game *game);
int		check_angle_rightx(t_game *game);
int		check_angle_righty(t_game *game);

//wall_secure_left
int		check_angle_leftx(t_game *game);
int		check_angle_lefty(t_game *game);
int		check_angle_lefty_s(t_game *game);
int		check_angle_leftx_s(t_game *game);

//mouse and sprites
int		capture_mouse(int button, int x, int y, t_game *game);
void	check_mouse_move(t_game *game);
void	draw_sprites(t_game *game, int i);
void	init_sprite_struct(t_game *game, int i, int j, int k);
void	check_distance_and_sort(t_game *game, int i);
int		in_fov(t_game *game, int i);
int		in_fov_2(t_game *game, int i);

// parsing functions

void	free_tab(char **tab);
void	free_map(t_map *map);
void	parse_error(int n, t_map *map);
void	parse_cub_file(int ac, char *path, t_map *map);
void	set_rgb_values(t_map *map, char c, char *str, int i);
void	init_map_structure(t_map *map);
int		is_valid_extension(char *path);
void	extract_cub_file_content(char *path, t_map *map);
void	grid_char_check(char **c, t_map *map, int i, int j);
char	*get_texture_path(char **content, char *dir, int i, t_map *map);
void	closed_map_check(char **grid, t_map *map, int x, int y);
void	default_textures_paths_if_necessary(t_map *map);
void	check_if_directory(char *path, t_map *map, int fd);
int		skip_spaces(char *str, int i);
void	useless_lines_check(char **content, t_map *map, int i);
void	copy_map_grid(char **src, t_map *map, int i, int j);
void	door_check(t_map *map);

#endif