/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_last_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-youb <ael-youb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 09:25:55 by ael-youb          #+#    #+#             */
/*   Updated: 2023/03/27 12:57:01 by ael-youb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	loop_loop_drawthreed(t_game *game, float height, float offset, int j)
{
	float	px;
	float	py;

	px = (game->player_x) / (HEIGHT / game->map.grid_height);
	py = (game->player_y) / (HEIGHT / game->map.grid_height);
	while (j < height + offset)
	{
		if (game->store.distance == game->store.dis_h && py > game->store.my)
			pixel_put(game->img, j, game->store.r, get_colour_from_texture(
					height, &game->south, game, j - offset));
		else if (game->store.distance == game->store.dis_h
			&& py < game->store.my)
			pixel_put(game->img, j, game->store.r,
				get_colour_from_texture(height, &game->north,
					game, j - offset));
		else if (game->store.distance == game->store.dis_v
			&& px > game->store.mx)
			pixel_put(game->img, j, game->store.r,
				get_colour_from_texture(height, &game->west, game, j - offset));
		else if (game->store.distance == game->store.dis_v
			&& px < game->store.mx)
			pixel_put(game->img, j, game->store.r,
				get_colour_from_texture(height, &game->east, game, j - offset));
		j++;
	}
}
