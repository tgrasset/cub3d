/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3D.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrasset <tgrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:38:02 by tgrasset          #+#    #+#             */
/*   Updated: 2023/04/05 12:42:57 by tgrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (x * data->ll + y * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	loop_loop_drawthree_d(t_game *game, float height, float offset, int j)
{
	float	px;
	float	py;

	px = (game->player_x) / game->pix;
	py = (game->player_y) / game->pix;
	while (j < height + offset)
	{
		if (game->map.grid[game->store.my][game->store.mx] == '3')
			pixel_put(game->img, j, game->store.r, get_colour_from_texture(
					height, &game->door, game, j - offset));
		else if (game->store.distance == game->store.dis_h
			&& py > game->store.my)
			pixel_put(game->img, j, game->store.r, get_colour_from_texture(
					height, &game->south, game, j - offset));
		else if (game->store.distance == game->store.dis_h
			&& py < game->store.my)
			pixel_put(game->img, j, game->store.r,
				get_colour_from_texture(height, &game->north,
					game, j - offset));
		else
			east_west_walls(game, height, offset, j);
		j++;
	}
}

void	loop_draw_three_d(t_game *game, float height, float offset)
{
	int		j;

	j = 0;
	while (j < offset)
	{
		pixel_put(game->img, j, (game->store.r),
			game->map.ceiling_int);
			j++;
	}
	loop_loop_drawthree_d(game, height, offset, j);
	j = height + offset;
	while (j <= HEIGHT)
	{
		pixel_put(game->img, j, (game->store.r),
			game->map.floor_int);
			j++;
	}
}

void	draw_three_d(t_game *game, float distance, float ra)
{
	float	height;
	float	offset;
	float	plan_fisheye;

	plan_fisheye = game->player_angle - ra;
	if (plan_fisheye < 0)
		plan_fisheye += 2 * PI;
	if (plan_fisheye > 2 * PI)
		plan_fisheye -= 2 * PI;
	distance = distance * cos(plan_fisheye);
	height = (32 * HEIGHT) / distance;
	game->store.actual_height = height;
	if (height > HEIGHT)
		height = HEIGHT;
	offset = (HEIGHT / 2) - height / 2;
	loop_draw_three_d(game, height, offset);
	game->ray_dist[game->store.r] = distance * distance;
}
