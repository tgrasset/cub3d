/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrasset <tgrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:16:51 by tgrasset          #+#    #+#             */
/*   Updated: 2023/04/05 12:25:41 by tgrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_sprite_colour(t_data *data, int width, int x, int y)
{
	char	*dst;
	int		height;

	height = width * 23 / 14;
	x = 14 * x / width;
	y = 23 * y / height;
	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	return (*(unsigned int *)dst);
}

int	choose_frame(t_game *game, int width, int x, int y)
{
	int	height;

	height = width * 23 / 14;
	if (game->frame > 0 && game->frame <= LOOP / 6)
		return (get_sprite_colour(&game->sp_1, width, x, y));
	else if (game->frame > LOOP / 6 && game->frame <= 2 * (LOOP / 6))
		return (get_sprite_colour(&game->sp_2, width, x, y));
	else if (game->frame > 2 * (LOOP / 6) && game->frame <= 3 * (LOOP / 6))
		return (get_sprite_colour(&game->sp_3, width, x, y));
	else if (game->frame > 3 * (LOOP / 6) && game->frame <= 4 * (LOOP / 6))
		return (get_sprite_colour(&game->sp_4, width, x, y));
	else if (game->frame > 4 * (LOOP / 6) && game->frame <= 5 * (LOOP / 6))
		return (get_sprite_colour(&game->sp_5, width, x, y));
	else
		return (get_sprite_colour(&game->sp_6, width, x, y));
}

void	display_sprite(t_game *game, float sx, float sy, int i)
{
	int	wid;
	int	hei;
	int	j;
	int	k;
	int	colour;

	wid = 300000 / game->sprites.dist[i];
	hei = wid * 23 / 14;
	j = (int)sx;
	while (j < (int)sx + wid)
	{
		k = (int)sy;
		while (k < (int)sy + hei)
		{
			colour = choose_frame(game, wid, j - (int)sx, k - (int)sy);
			if (j > 0 && j < RAY_NUMBER && k > 0 && k < HEIGHT
				&& colour != 0x00FF2F
				&& game->sprites.dist[i] < game->ray_dist[j])
				pixel_put(game->img, k, j, colour);
			k++;
		}
		j++;
	}
}

void	draw_sprites(t_game *game, int i)
{
	float	cs;
	float	sn;
	float	sx;
	float	sy;
	float	sz;

	check_distance_and_sort(game, 0);
	while (++i < game->map.sprite_nb)
	{
		if (game->sprites.dist[i] < 1000 || in_fov(game, i) == 0
			|| game->sprites.dist[i] > 200000)
			continue ;
		game->sprites.rel_x = game->sprites.sp_x[i] - game->player_x;
		game->sprites.rel_y = game->sprites.sp_y[i] - game->player_y;
		sz = 10;
		cs = cos(game->player_angle);
		sn = sin(game->player_angle);
		sx = game->sprites.rel_y * cs - game->sprites.rel_x * sn;
		sy = game->sprites.rel_x * cs + game->sprites.rel_y * sn;
		sx = (sx * 900.0 / sy) + (RAY_NUMBER / 2);
		sy = (sz * 900.0 / sy) + (HEIGHT / 2);
		display_sprite(game, sx, sy, i);
	}
}
