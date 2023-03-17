/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-youb <ael-youb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:53:57 by ael-youb          #+#    #+#             */
/*   Updated: 2023/03/17 17:26:33 by ael-youb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	mapSize=8;
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
}

float dist(float ax,float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	draw_ray(t_game *game)
{
	int	r, mx, my, mp, dof; float rx, ry, ra, xo, yo;
	float dis_h=1000000, hx = game->player_x, hy = game->player_y;
	float dis_v=1000000, vx = game->player_x, vy = game->player_y;

	ra = game->player_angle;
	r = 0;
	while(r < 1) // on ne cast qu'un seul ray pour l'instant
	{
		//checker les lignes horizontales
		dof = 0;
		float a_tan = -1/tan(ra);
		if (ra > PI)
		{
			ry = (((int)game->player_y>>6)<<6) - 0.0001;
			rx = (game->player_y - ry) * a_tan + game->player_x;
			yo = -64;
			xo = -yo * a_tan;
		}
		if (ra < PI)
		{
			ry = (((int)game->player_y>>6)<<6) + 64;
			rx = (game->player_y - ry) * a_tan + game->player_x;
			yo = 64;
			xo = -yo * a_tan;
		}
		if (ra == PI || ra == 0)
		{
			rx = game->player_x;
			ry = game->player_y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx)>>6;
			my = (int)(ry)>>6;
			mp = my * mapSize + mx;
			if (mp > 0 && mp < mapSize*mapSize && map[mp] == 1)
			{
				hx = rx;
				hy = ry;
				dis_h = dist(game->player_x, game->player_y, hx, hy);
				dof = 8;
			}
			else
			{
				rx+=xo;
				ry+=yo;
				dof++;
			}
		}
		//checker les lignes verticales
		dof = 0;
		float n_tan = -tan(ra);
		if (ra > P2 && ra < P3)
		{
			rx = (((int)game->player_x>>6)<<6) - 0.0001;
			ry = (game->player_x - rx) * n_tan + game->player_y;
			xo = -64;
			yo = -xo * n_tan;
		}
		if (ra < P2 || ra > P3)
		{
			rx = (((int)game->player_x>>6)<<6) + 64;
			ry = (game->player_x - rx) * n_tan + game->player_y;
			xo = 64;
			yo = -xo * n_tan;
		}
		if (ra == PI || ra == 0)
		{
			rx = game->player_x;
			ry = game->player_y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx)>>6;
			my = (int)(ry)>>6;
			mp = my * mapSize + mx;
			if (mp > 0 && mp < mapSize*mapSize && map[mp] == 1)
			{
				vx = rx;
				vy = ry;
				dis_v = dist(game->player_x, game->player_y, vx, vy);
				dof = 8;
			}
			else
			{
				rx+=xo;
				ry+=yo;
				dof++;
			}
		}
		if (dis_v < dis_h)
		{
			rx = vx;
			ry = vy;
		}
		if (dis_v > dis_h)
		{
			rx = hx;
			ry = hy;
		}
		mx = (int)(rx)>>6;
		my = (int)(ry)>>6;
		mp = my * mapSize + mx;
		printf("found wall at x:%d y:%d\n", mx,my);
		if (mp < mapSize*mapSize)
		{
			int i = ry;
			int j = rx;
			while (i < ry + 2)
			{
				while (j < rx + 2)
				{
					pixel_put(game->img, i, j,
						0x80090888);
					j++;
				}
				j = rx;
				i++;
			}
		}
		r++;
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
	draw_ray(game);
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
	while (x < mapSize)
	{
		while (y < mapSize)
		{
			xo = x * 64;
			yo = y * 64;
			while (xo < ((x + 1) * 64) - 1) // 10px offset entre chaque case
			{
				while (yo < ((y + 1) * 64) - 1)
				{
					pixel_put(game->img, yo, xo,
						0x00000000);
					if (map[y*mapSize+x] == 1)
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
