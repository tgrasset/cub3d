/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-youb <ael-youb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 23:05:57 by ael-youb          #+#    #+#             */
/*   Updated: 2023/03/18 23:10:10 by ael-youb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

extern int mapSize;
extern int map[];
extern int window_size;

//pick the shorted distance
void	pick_v_or_h(t_game *game, int pix)
{
	game->store->color = 0;
	if (game->store->dis_v < game->store->dis_h)
	{
		game->store->rx = game->store->vx;
		game->store->ry = game->store->vy;
		game->store->distance = game->store->dis_v;
		game->store->color = 1;
	}
	if (game->store->dis_v > game->store->dis_h)
	{
		game->store->rx = game->store->hx;
		game->store->ry = game->store->hy;
		game->store->distance = game->store->dis_h;
		game->store->color = 0;
	}
	game->store->mx = (int)(game->store->rx) / pix;
	game->store->my = (int)(game->store->ry) / pix;
	game->store->mp = game->store->my * mapSize + game->store->mx;
}

void	init_draw_ray(t_game *game)
{
	game->store->dis_h = 1000000;
	game->store->hx = game->player_x;
	game->store->hy = game->player_y;

	game->store->dis_v = 1000000;
	game->store->vx = game->player_x;
	game->store->vy = game->player_y;

	game->store->ra = game->player_angle - DR * 30;
	if (game->store->ra < 0)
	{
		game->store->ra += 2 * PI;
	}
	if (game->store->ra > 2 * PI)
	{
		game->store->ra -= 2 * PI;
	}
	game->store->r = 0;
}

void	draw_minimap_dot(t_game *game)
{
	if (game->store->mp < mapSize * mapSize)
	{
		int i = game->store->ry;
		int j = game->store->rx;
		while (i < game->store->ry + 2)
		{
			while (j < game->store->rx + 2)
			{
				pixel_put(game->img, i, j,
							0x80090888);
				j++;
			}
			j = game->store->rx;
			i++;
		}
	}
}