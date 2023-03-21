/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrasset <tgrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:53:57 by ael-youb          #+#    #+#             */
/*   Updated: 2023/03/21 15:53:51 by tgrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (x * data->ll + y * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_player(t_game *game)
{
	int	i;
	int	j;

	i = game->player_y;
	j = game->player_x;
	while (i < game->player_y + 5)
	{
		while (j < game->player_x + 5)
		{
			pixel_put(game->img, i, j,
				0x80090888);
			j++;
		}
		j = game->player_x;
		i++;
	}
}

float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	loop_draw_three_d(t_game *game, float height, float offset)
{
	int		cpt;
	int		j;

	j = offset;
	cpt = 0;
	while (cpt < 1)
	{
		while (j < height + offset)
		{
			if (game->store->color)
				pixel_put(game->img, j, (530 + game->store->r) + cpt,
					0x00002888);
			else
				pixel_put(game->img, j, (530 + game->store->r) + cpt,
					0x80090888);
			j++;
		}
		j = offset;
		cpt++;
	}
}

void	draw_three_d(t_game *game, float distance, float ra)
{
	float	height;
	float	offset;
	float	plan_fisheye;

	plan_fisheye = game->player_angle - ra;
	if (plan_fisheye < 0)
		plan_fisheye += 2 * PI;
	if (plan_fisheye > 2 * PI)
		plan_fisheye -= 2 * PI;
	distance = distance * cos(plan_fisheye);
	height = (8 * 2 * 320) / distance; //bizarre value
	if (height > 320)
		height = 320;
	offset = 200 - height / 2;
	loop_draw_three_d(game, height, offset);
}

void	add_to_image(t_game *game)
{
	float	i;
	float	j;

	i = 0;
	j = 0;
	while (i < 512)
	{
		while (j < 1024)
		{
			pixel_put(game->img, i, j,
				0x80808080);
			j++;
		}
		j = 0;
		i++;
	}
	draw_map(game);
	draw_player(game);
	draw_ray(game);
	mlx_put_image_to_window(game->win->mlx, game->win->mlx_win, game->img->img, 0, 0);
}

void	draw_map(t_game *game)
{
	int	x;
	int	y;
	int	xo;
	int	yo;
	int	pix;

	x = 0;
	y = 0;
	pix = 512 / (game->map.grid_width);
	while (x < game->map.grid_width)
	{
		while (y < game->map.grid_width)
		{
			xo = x * pix;
			yo = y * pix;
			while (xo < ((x + 1) * pix) - 1) // 10px offset entre chaque case
			{
				while (yo < ((y + 1) * pix) - 1)
				{
					pixel_put(game->img, xo, yo,
						0x00000000);
					if (game->map.grid[x][y] == '1')
					{
						pixel_put(game->img, xo, yo,
							0x88800000);
					}
					else
					{
						pixel_put(game->img, xo, yo,
							0x99999999);
					}
					yo++;
				}
				yo = y * pix;
				xo++;
			}
			y++;
		}
		x++;
		y = 0;
	}
}

void	load_textures(t_game *game)
{
	game->north.img = mlx_xpm_file_to_image(game->win->mlx, game->map.north,
		&game->north.w, &game->north.h);
	game->south.img = mlx_xpm_file_to_image(game->win->mlx, game->map.south,
		&game->south.w, &game->south.h);
	game->east.img = mlx_xpm_file_to_image(game->win->mlx, game->map.east,
		&game->east.w, &game->east.h);
	game->west.img = mlx_xpm_file_to_image(game->win->mlx, game->map.west,
		&game->west.w, &game->west.h);
	if (game->north.img == NULL || game->south.img == NULL
		|| game->east.img == NULL || game->west.img == NULL)
	{
		ft_putendl_fd("Error\nOne or more textures couldn't be loaded", 2);
		close_program(game);
	}
	game->north.addr = mlx_get_data_addr(game->north.img, &game->north.bpp,
		&game->north.ll, &game->north.endian);
	game->south.addr = mlx_get_data_addr(game->south.img, &game->south.bpp,
		&game->south.ll, &game->south.endian);
	game->east.addr = mlx_get_data_addr(game->east.img, &game->east.bpp,
		&game->east.ll, &game->east.endian);
	game->west.addr = mlx_get_data_addr(game->west.img, &game->west.bpp,
		&game->west.ll, &game->west.endian);
}

void	init_mlx(t_game *game)
{
	t_vars	win;
	t_data	img;

	win.mlx = mlx_init();
	win.mlx_win = mlx_new_window(win.mlx, 1024, 512, "Louveteau 3D");
	img.img = mlx_new_image(win.mlx, 1024, 512);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.ll, &img.endian);
	game->win = &win;
	game->img = &img;
	load_textures(game);
	add_to_image(game);
	mlx_put_image_to_window(win.mlx, win.mlx_win, game->img->img, 0, 0);
	mlx_hook(win.mlx_win, 2, 1L << 0, hook_slide, game);
	mlx_hook(win.mlx_win, 17, 0L, destroy_window, game);
	mlx_loop(win.mlx);
}
