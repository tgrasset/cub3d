/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrasset <tgrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:23:15 by tgrasset          #+#    #+#             */
/*   Updated: 2023/04/03 17:30:06 by tgrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	util_draw_player(t_game *game, int cases, int pix)
{
	int	i;
	int	j;

	i = cases * pix + (pix / 2) + game->player_deltax;
	j = cases * pix + (pix / 2) + game->player_deltay;
	while (i < ((cases * pix + (pix / 2)) + 3) + game->player_deltax)
	{
		while (j < ((cases * pix + (pix / 2)) + 3) + game->player_deltay)
		{
			pixel_put(game->img, j, i,
				0x00FF0000);
			j++;
		}
		j = cases * pix + (pix / 2) + game->player_deltay;
		i++;
	}
}

void	draw_minimap_dot(t_game *game)
{
	int	i;
	int	j;

	if (game->store.mp < game->map.grid_height * game->map.grid_height
		&& game->store.mx > 0 && game->store.my > 0)
	{	
		j = game->store.rx;
		i = game->store.ry;
		while (i < game->store.ry + 1)
		{
			while (j < game->store.rx + 1)
			{
				pixel_put(game->img, i, j,
					0x80090888);
				j++;
			}
			j = game->store.rx;
			i++;
		}
	}
}
