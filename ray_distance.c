/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-youb <ael-youb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:12:26 by tgrasset          #+#    #+#             */
/*   Updated: 2023/04/04 17:21:30 by tgrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	pick_v_or_h(t_game *game)
{
	game->store.color = 0;
	if (game->store.dis_v <= game->store.dis_h)
	{
		game->store.rx = game->store.vx;
		game->store.ry = game->store.vy;
		game->store.distance = game->store.dis_v;
		game->store.color = 1;
	}
	if (game->store.dis_v > game->store.dis_h)
	{
		game->store.rx = game->store.hx;
		game->store.ry = game->store.hy;
		game->store.distance = game->store.dis_h;
		game->store.color = 0;
	}
	game->store.mx = (int)(game->store.rx) / game->pix;
	game->store.my = (int)(game->store.ry) / game->pix;
	game->store.mp = game->store.my * game->map.grid_height + game->store.mx;
}

void	loop_distance_h(t_game *game)
{
	while (game->store.dof < game->store.dof_max)
	{
		game->store.mx = (int)(game->store.rx) / game->pix;
		game->store.my = (int)(game->store.ry) / game->pix;
		game->store.mp = game->store.my
			* game->map.grid_height + game->store.mx;
		if (game->store.my >= 0
			&& game->store.mx >= 0
			&& game->store.my < game->map.grid_height
			&& game->store.mx < game->map.grid_height
			&& is_wall_or_door(game))
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

void	loop_distance_v(t_game *game)
{
	while (game->store.dof < game->store.dof_max)
	{
		game->store.mx = (int)(game->store.rx) / game->pix;
		game->store.my = (int)(game->store.ry) / game->pix;
		game->store.mp = game->store.my
			* game->map.grid_height + game->store.mx;
		if (game->store.my >= 0
			&& game->store.mx >= 0
			&& game->store.my < game->map.grid_height
			&& game->store.mx < game->map.grid_height
			&& is_wall_or_door(game))
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

void	distance_h(t_game *game)
{
	game->store.dof = 0;
	if (game->store.ra > PI)
	{
		game->store.ry = (((int)game->player_y / game->pix)
				* game->pix) - 0.001;
		game->store.rx = (game->player_y - game->store.ry)
			* (-1 / tan(game->store.ra)) + game->player_x;
		game->store.yo = -game->pix;
		game->store.xo = -game->store.yo * (-1 / tan(game->store.ra));
	}
	if (game->store.ra < PI)
	{
		game->store.ry = (((int)game->player_y / game->pix)
				* game->pix) + game->pix;
		game->store.rx = (game->player_y - game->store.ry)
			* (-1 / tan(game->store.ra)) + game->player_x;
		game->store.yo = game->pix;
		game->store.xo = -game->store.yo * (-1 / tan(game->store.ra));
	}
	if (game->store.ra == PI || game->store.ra == 0)
		ray_special_case(game);
	loop_distance_h(game);
}

void	distance_v(t_game *game)
{
	game->store.dof = 0;
	if (game->store.ra > P2 && game->store.ra < P3)
	{
		game->store.rx = (((int)game->player_x / game->pix)
				* game->pix) - 0.001;
		game->store.ry = (game->player_x - game->store.rx)
			* (-tan(game->store.ra)) + game->player_y;
		game->store.xo = -game->pix;
		game->store.yo = -game->store.xo * (-tan(game->store.ra));
	}
	if (game->store.ra < P2 || game->store.ra > P3)
	{
		game->store.rx = (((int)game->player_x / game->pix)
				* game->pix) + game->pix;
		game->store.ry = (game->player_x - game->store.rx)
			* (-tan(game->store.ra)) + game->player_y;
		game->store.xo = game->pix;
		game->store.yo = -game->store.xo * (-tan(game->store.ra));
	}
	if (game->store.ra == PI || game->store.ra == 0)
		ray_special_case(game);
	loop_distance_v(game);
}
