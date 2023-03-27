/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-youb <ael-youb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 23:20:40 by ael-youb          #+#    #+#             */
/*   Updated: 2023/03/27 12:44:33 by ael-youb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//attention, y et x inverses dans map
void	loop_distance_h(t_game *game, int pix)
{
	while (game->store.dof < game->store.dof_max)
	{
		game->store.mx = (int)(game->store.rx) / pix;
		game->store.my = (int)(game->store.ry) / pix;
		game->store.mp = game->store.my
			* game->map.grid_height + game->store.mx;
		if (game->store.my >= 0
			&& game->store.mx >= 0
			&& game->store.my < game->map.grid_height
			&& game->store.mx < game->map.grid_height
			&& game->map.grid[game->store.my][game->store.mx] == '1')
		{
			game->store.hx = game->store.rx;
			game->store.hy = game->store.ry;
			game->store.dis_h = dist(game->player_x, game->player_y,
					game->store.hx, game->store.hy);
			game->store.dof = game->store.dof_max;
		}
		else
		{
			game->store.rx += game->store.xo;
			game->store.ry += game->store.yo;
			game->store.dof++;
		}
	}
}

void	loop_distance_v(t_game *game, int pix)
{
	while (game->store.dof < game->store.dof_max)
	{
		game->store.mx = (int)(game->store.rx) / pix;
		game->store.my = (int)(game->store.ry) / pix;
		game->store.mp = game->store.my
			* game->map.grid_height + game->store.mx;
		if (game->store.my >= 0
			&& game->store.mx >= 0
			&& game->store.my < game->map.grid_height
			&& game->store.mx < game->map.grid_height
			&& game->map.grid[game->store.my][game->store.mx] == '1')
		{
			game->store.vx = game->store.rx;
			game->store.vy = game->store.ry;
			game->store.dis_v = dist(game->player_x, game->player_y,
					game->store.vx, game->store.vy);
			game->store.dof = game->store.dof_max;
		}
		else
		{
			game->store.rx += game->store.xo;
			game->store.ry += game->store.yo;
			game->store.dof++;
		}
	}
}

// check horizontal lines
void	distance_h(t_game *game, int pix)
{
	game->store.dof = 0;
	if (game->store.ra > PI)
	{
		game->store.ry = (((int)game->player_y / pix) * pix) - 0.001;
		game->store.rx = (game->player_y - game->store.ry)
			* (-1 / tan(game->store.ra)) + game->player_x;
		game->store.yo = -pix;
		game->store.xo = -game->store.yo * (-1 / tan(game->store.ra));
	}
	if (game->store.ra < PI)
	{
		game->store.ry = (((int)game->player_y / pix) * pix) + pix;
		game->store.rx = (game->player_y - game->store.ry)
			* (-1 / tan(game->store.ra)) + game->player_x;
		game->store.yo = pix;
		game->store.xo = -game->store.yo * (-1 / tan(game->store.ra));
	}
	if (game->store.ra == PI || game->store.ra == 0)
	{
		game->store.rx = game->player_x;
		game->store.ry = game->player_y;
		game->store.dof = game->store.dof_max;
	}
	loop_distance_h(game, pix);
}

// check vertical lines
void	distance_v(t_game *game, int pix)
{
	game->store.dof = 0;
	if (game->store.ra > P2 && game->store.ra < P3)
	{
		game->store.rx = (((int)game->player_x / pix) * pix) - 0.001;
		game->store.ry = (game->player_x - game->store.rx)
			* (-tan(game->store.ra)) + game->player_y;
		game->store.xo = -pix;
		game->store.yo = -game->store.xo * (-tan(game->store.ra));
	}
	if (game->store.ra < P2 || game->store.ra > P3)
	{
		game->store.rx = (((int)game->player_x / pix) * pix) + pix;
		game->store.ry = (game->player_x - game->store.rx)
			* (-tan(game->store.ra)) + game->player_y;
		game->store.xo = pix;
		game->store.yo = -game->store.xo * (-tan(game->store.ra));
	}
	if (game->store.ra == PI || game->store.ra == 0)
	{
		game->store.rx = game->player_x;
		game->store.ry = game->player_y;
		game->store.dof = game->store.dof_max;
	}
	loop_distance_v(game, pix);
}

void	draw_rays(t_game *game)
{
	int	pix;

	pix = HEIGHT / game->map.grid_height;
	init_draw_ray(game);
	while (game->store.r < RAY_NUMBER)
	{
		reinitialize_distances(game);
		distance_h(game, pix);
		distance_v(game, pix);
		pick_v_or_h(game, pix);
		game->store.r++;
		draw_three_d(game, game->store.distance, game->store.ra);
		game->store.ra += (DR / 18);
		if (game->store.ra < 0)
			game->store.ra += 2 * PI;
		if (game->store.ra > 2 * PI)
			game->store.ra -= 2 * PI;
	}
}
