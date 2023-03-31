/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_five.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-youb <ael-youb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 23:49:28 by ael-youb          #+#    #+#             */
/*   Updated: 2023/03/30 23:55:41 by ael-youb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_wallhack_strafel(t_game *game)
{
	int	mx;
	int	my;
	int	mx_two;
	int	my_two;

	mx = (int)(game->player_x - check_angle_leftx_s(game))
		/ (HEIGHT / game->map.grid_height);
	my = (int)(game->player_y - check_angle_lefty_s(game))
		/ (HEIGHT / game->map.grid_height);
	mx_two = (int)(game->player_x - check_angle_rightx_s(game))
		/ (HEIGHT / game->map.grid_height);
	my_two = (int)(game->player_y - check_angle_righty_s(game))
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

int	check_wallhack_strafer(t_game *game)
{
	int	mx;
	int	my;
	int	mx_two;
	int	my_two;

	mx = (int)(game->player_x + check_angle_leftx_s(game))
		/ (HEIGHT / game->map.grid_height);
	my = (int)(game->player_y + check_angle_lefty_s(game))
		/ (HEIGHT / game->map.grid_height);
	mx_two = (int)(game->player_x + check_angle_rightx_s(game))
		/ (HEIGHT / game->map.grid_height);
	my_two = (int)(game->player_y + check_angle_righty_s(game))
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