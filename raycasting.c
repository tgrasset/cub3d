/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrasset <tgrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 23:20:40 by ael-youb          #+#    #+#             */
/*   Updated: 2023/04/03 17:47:04 by tgrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_draw_ray(t_game *game)
{
	game->store.dis_h = 1000000;
	game->store.hx = game->player_x;
	game->store.hy = game->player_y;
	game->store.dis_v = 1000000;
	game->store.vx = game->player_x;
	game->store.vy = game->player_y;
	game->store.ra = game->player_angle
		- (((DR / game->scale_ray) * RAY_NUMBER) / 2);
	if (game->store.ra < 0)
	{
		game->store.ra += 2 * PI;
	}
	if (game->store.ra > 2 * PI)
	{
		game->store.ra -= 2 * PI;
	}
	game->store.r = 0;
}

void	reinitialize_distances(t_game *game)
{
	game->store.dis_h = 1000000;
	game->store.hx = game->player_x;
	game->store.hy = game->player_y;
	game->store.dis_v = 1000000;
	game->store.vx = game->player_x;
	game->store.vy = game->player_y;
}

void	draw_rays(t_game *game)
{
	init_draw_ray(game);
	while (game->store.r < RAY_NUMBER)
	{
		reinitialize_distances(game);
		distance_h(game);
		distance_v(game);
		pick_v_or_h(game);
		game->store.r++;
		draw_three_d(game, game->store.distance, game->store.ra);
		game->store.ra += (DR / game->scale_ray);
		if (game->store.ra < 0)
			game->store.ra += 2 * PI;
		if (game->store.ra > 2 * PI)
			game->store.ra -= 2 * PI;
	}
}
