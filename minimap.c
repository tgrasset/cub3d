/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrasset <tgrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:28:09 by tgrasset          #+#    #+#             */
/*   Updated: 2023/04/03 17:30:01 by tgrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_player(t_game *game)
{
	int	i;
	int	j;
	int	cases;
	int	pix;

	cases = 3;
	if (game->map.grid_height < 6)
		cases = game->map.grid_height / 2;
	pix = game->pix;
	i = cases * pix + (pix / 2);
	j = cases * pix + (pix / 2);
	while (i < (cases * pix + (pix / 2)) + 4)
	{
		while (j < (cases * pix + (pix / 2)) + 4)
		{
			pixel_put(game->img, i, j,
				0x80090888);
			j++;
		}
		j = cases * pix + (pix / 2);
		i++;
	}
	//util_draw_player(game, cases, pix);
}

void	init_minimap(t_minimap *minimap, t_game *game)
{
	minimap->cases = 3;
	if (game->map.grid_height < 6)
		minimap->cases = game->map.grid_height / 2;
	minimap->x = (int)(game->player_x) / game->pix;
	minimap->y = (int)(game->player_y) / game->pix;
	minimap->x = minimap->x - minimap->cases;
	minimap->y = minimap->y - minimap->cases;
	minimap->x_origin = 0;
	minimap->y_origin = 0;
	minimap->pix = game->pix;
}

void	loop_minimap(t_game *game, t_minimap *minimap)
{
	while (minimap->xo < ((minimap->x_origin + 1) * minimap->pix))
	{
		while (minimap->yo < ((minimap->y_origin + 1) * minimap->pix))
		{
			if (minimap->x < 0 || minimap->x >= game->map.grid_height)
				break ;
			if (minimap->y < 0 || minimap->y >= game->map.grid_height)
				break ;
			pixel_put(game->img, minimap->yo, minimap->xo,
				0x88800000);
			if (game->map.grid[minimap->y][minimap->x] == '1')
				pixel_put(game->img, minimap->yo, minimap->xo,
					0x88800000);
			else
				pixel_put(game->img, minimap->yo, minimap->xo,
					0x99999999);
			minimap->yo++;
		}
		minimap->yo = minimap->y_origin * minimap->pix;
		minimap->xo++;
	}
}

void	background_minimap(t_game *game, t_minimap *minimap)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < minimap->pix * minimap->cases * 2)
	{
		while (j < minimap->pix * minimap->cases * 2)
		{
			pixel_put(game->img, j, i,
				0x88800000);
			j++;
		}
		j = 0;
		i++;
	}
}

void	draw_map(t_game *game)
{
	t_minimap	minimap;

	init_minimap(&minimap, game);
	background_minimap(game, &minimap);
	while (minimap.x < (int)(game->player_x)
		/ minimap.pix + minimap.cases)
	{
		while (minimap.y < (int)(game->player_y) /
			minimap.pix + minimap.cases)
		{
			minimap.xo = minimap.x_origin * minimap.pix;
			minimap.yo = minimap.y_origin * minimap.pix;
			loop_minimap(game, &minimap);
			minimap.y++;
			minimap.y_origin++;
		}
		minimap.x++;
		minimap.x_origin++;
		minimap.y_origin = 0;
		minimap.y = (int)(game->player_y) / game->pix;
		minimap.y = minimap.y - minimap.cases;
	}
}
