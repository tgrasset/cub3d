/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-youb <ael-youb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:53:57 by ael-youb          #+#    #+#             */
/*   Updated: 2023/03/14 16:10:10 by ael-youb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int map[]= 
{
    1,1,1,1,1,1,1,1,
    1,0,1,0,0,0,0,1,
    1,0,1,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,1,0,1,
    1,1,1,1,1,1,1,1,
};

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
	while (i < game->player_y + 10)
	{
		while (j < game->player_x + 10)
		{
			pixel_put(game->img, i, j,
				0x80090888);
			j++;
		}
		j = game->player_x;
		i++;
	}
	i = game->player_y;
	j = game->player_x;
	int countx = 10;
	int	county = 10;
	while (countx)
	{
		while (county)
		{
			pixel_put(game->img, i, j,
				0x80090888);
			j -= game->player_deltax * 1;
			county--;
		}
		j = game->player_x;
		county = 10;
		countx--;
		i -= game->player_deltay * 1;
	}
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
	mlx_put_image_to_window(game->win->mlx, game->win->mlx_win, game->img->img, 0, 0);
}

void	draw_map(t_game *game)
{
	int	x;
	int	y;
	int	xo;
	int	yo;
	//int	color;

	x = 0;
	y = 0;
	while (x < 8)
	{
		while (y < 8)
		{
			xo = x * 64;
			yo = y * 64;
			while (xo < ((x + 1) * 64) - 1) // 10px offset entre chaque case
			{
				while (yo < ((y + 1) * 64) - 1)
				{
					pixel_put(game->img, yo, xo,
						0x00000000);
					if (map[y*8+x] == 1)
					{
						pixel_put(game->img, yo, xo,
							0x88800000);
					}
					else
					{
						pixel_put(game->img, yo, xo,
							0x99999999);
					}
					yo++;
				}
				yo = y * 64;
				xo++;
			}
			y++;
		}
		x++;
		y = 0;
	}
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
	add_to_image(game);
	mlx_put_image_to_window(win.mlx, win.mlx_win, game->img->img, 0, 0);
	//mlx_key_hook(win.mlx_win, hook_slide, game);
	mlx_hook(win.mlx_win, 2, 1L<<0, hook_slide, game);
	mlx_hook(win.mlx_win, 17, 0L, destroy_window, game);
	mlx_loop(win.mlx);
}
