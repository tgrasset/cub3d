/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-youb <ael-youb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 09:03:21 by ael-youb          #+#    #+#             */
/*   Updated: 2023/04/03 15:08:52 by ael-youb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

int	get_colour_from_texture(int height, t_data *data, t_game *game, int wall_y)
{
	char			*dst;
	int				x;
	int				y;
	float			tmp;

	if (game->store.distance == game->store.dis_h)
		tmp = game->store.rx / game->pix;
	else
		tmp = game->store.ry / game->pix;
	tmp -= (int)tmp;
	tmp *= 1000;
	if (data == &game->north || data == &game->west)
		tmp = 1000 - tmp;
	y = (int)tmp;
	y = data->w * y / 1000;
	if (height == game->store.actual_height)
		x = wall_y * data->h / height;
	else
		x = (wall_y + ((game->store.actual_height - height) / 2))
			* data->h / game->store.actual_height;
	dst = data->addr + (x * data->ll + y * (data->bpp / 8));
	return (*(unsigned int *)dst);
}

void	util_draw_player(t_game *game, int cases, int pix)
{
	int	i;
	int	j;

	i = cases * pix + pix + game->player_deltax;
	j = cases * pix + pix + game->player_deltay;
	while (i < ((cases * pix + pix) + 3) + game->player_deltax)
	{
		while (j < ((cases * pix + pix) + 3) + game->player_deltay)
		{
			pixel_put(game->img, j, i,
				0x00FF0000);
			j++;
		}
		j = cases * pix + pix + game->player_deltay;
		i++;
	}
}
