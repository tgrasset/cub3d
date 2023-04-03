/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_secure.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrasset <tgrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:52:21 by tgrasset          #+#    #+#             */
/*   Updated: 2023/04/03 18:46:15 by tgrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_wallhack_strafe_l(t_game *game)
{
	int	mx;
	int	my;
	int	mx_two;
	int	my_two;

	mx = (int)(game->player_x - check_angle_leftx_s(game))
		/ game->pix;
	my = (int)(game->player_y - check_angle_lefty_s(game))
		/ game->pix;
	mx_two = (int)(game->player_x - check_angle_rightx_s(game))
		/ game->pix;
	my_two = (int)(game->player_y - check_angle_righty_s(game))
		/ game->pix;
	if (mx < game->map.grid_height && mx > 0
		&& mx_two < game->map.grid_height && mx_two > 0)
	{
		if (my < game->map.grid_height && my > 0
			&& my_two < game->map.grid_height && my_two > 0)
		{
			if (game->map.grid[my][mx] != '1'
				&& game->map.grid[my_two][mx_two] != '1')
				return (1);
		}
	}
	return (0);
}

int	check_wallhack_strafe_r(t_game *game)
{
	int	mx;
	int	my;
	int	mx_two;
	int	my_two;

	mx = (int)(game->player_x + check_angle_leftx_s(game))
		/ game->pix;
	my = (int)(game->player_y + check_angle_lefty_s(game))
		/ game->pix;
	mx_two = (int)(game->player_x + check_angle_rightx_s(game))
		/ game->pix;
	my_two = (int)(game->player_y + check_angle_righty_s(game))
		/ game->pix;
	if (mx < game->map.grid_height && mx > 0
		&& mx_two < game->map.grid_height && mx_two > 0)
	{
		if (my < game->map.grid_height && my > 0
			&& my_two < game->map.grid_height && my_two > 0)
		{
			if (game->map.grid[my][mx] != '1'
				&& game->map.grid[my_two][mx_two] != '1')
				return (1);
		}
	}
	return (0);
}

int	check_wallhack_backward(t_game *game)
{
	int	mx;
	int	my;
	int	mx_two;
	int	my_two;

	mx = (int)(game->player_x - check_angle_leftx(game))
		/ game->pix;
	my = (int)(game->player_y - check_angle_lefty(game))
		/ game->pix;
	mx_two = (int)(game->player_x - check_angle_rightx(game))
		/ game->pix;
	my_two = (int)(game->player_y - check_angle_righty(game))
		/ game->pix;
	if (mx < game->map.grid_height && mx > 0
		&& mx_two < game->map.grid_height && mx_two > 0)
	{
		if (my < game->map.grid_height && my > 0
			&& my_two < game->map.grid_height && my_two > 0)
		{
			if (game->map.grid[my][mx] != '1'
				&& game->map.grid[my_two][mx_two] != '1')
				return (1);
		}
	}
	return (0);
}

int	check_wallhack(t_game *game)
{
	int	mx;
	int	my;
	int	mx_two;
	int	my_two;

	mx = (int)(game->player_x + check_angle_leftx(game))
		/ game->pix;
	my = (int)(game->player_y + check_angle_lefty(game))
		/ game->pix;
	mx_two = (int)(game->player_x + check_angle_rightx(game))
		/ game->pix;
	my_two = (int)(game->player_y + check_angle_righty(game))
		/ game->pix;
	if (mx < game->map.grid_height && mx > 0
		&& mx_two < game->map.grid_height && mx_two > 0)
	{
		if (my < game->map.grid_height && my > 0
			&& my_two < game->map.grid_height && my_two > 0)
		{
			if (game->map.grid[my][mx] != '1'
				&& game->map.grid[my_two][mx_two] != '1')
				return (1);
		}
	}
	return (0);
}
