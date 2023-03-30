/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-youb <ael-youb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 01:58:30 by ael-youb          #+#    #+#             */
/*   Updated: 2023/03/30 02:20:25 by ael-youb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_angle_leftx(t_game *game)
{
	float	angle;

	angle = game->player_angle - (20 * DR);
	if (angle < 0)
		angle += 2 * PI;
	if (angle < 0)
		angle += 2 * PI;
	return (cos(game->player_angle) * 5);
}

int	check_angle_lefty(t_game *game)
{
	float	angle;

	angle = game->player_angle - (20 * DR);
	if (angle < 0)
		angle += 2 * PI;
	if (angle < 0)
		angle += 2 * PI;
	return (sin(game->player_angle) * 5);
}

int	check_angle_rightx(t_game *game)
{
	float	angle;

	angle = game->player_angle + (20 * DR);
	if (angle < 0)
		angle += 2 * PI;
	if (angle < 0)
		angle += 2 * PI;
	return (cos(game->player_angle) * 5);
}

int	check_angle_righty(t_game *game)
{
	float	angle;

	angle = game->player_angle + (20 * DR);
	if (angle < 0)
		angle += 2 * PI;
	if (angle < 0)
		angle += 2 * PI;
	return (sin(game->player_angle) * 5);
}

int	check_wallhack(t_game *game)
{
	int	mx;
	int	my;
	int	mx_two;
	int	my_two;

	mx = (int)(game->player_x + check_angle_leftx(game) * 2)
		/ (HEIGHT / game->map.grid_height);
	my = (int)(game->player_y + check_angle_lefty(game) * 2)
		/ (HEIGHT / game->map.grid_height);
	mx_two = (int)(game->player_x + check_angle_rightx(game) * 2)
		/ (HEIGHT / game->map.grid_height);
	my_two = (int)(game->player_y + check_angle_righty(game) * 2)
		/ (HEIGHT / game->map.grid_height);
	if (mx < game->map.grid_height && mx > 0
		&& mx_two < game->map.grid_height && mx_two > 0)
	{
		if (my < game->map.grid_height && my > 0
			&& my_two < game->map.grid_height && my_two > 0)
		{
			if (game->map.grid[my][mx] == '0'
				&& game->map.grid[my_two][mx_two] == '0')
				return (1);
		}
	}
	return (0);
}
