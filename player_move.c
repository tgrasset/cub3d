/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrasset <tgrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:48:06 by tgrasset          #+#    #+#             */
/*   Updated: 2023/04/04 15:04:13 by tgrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	go_backward(t_game *game)
{
	int	mx;
	int	my;

	mx = (int)(game->player_x - (game->player_deltax * 2))
		/ game->pix;
	my = (int)(game->player_y - (game->player_deltay * 2))
		/ game->pix;
	if (mx < game->map.grid_height && mx > 0)
	{
		if (my < game->map.grid_height && my > 0)
		{
			if (game->map.grid[my][mx] != '1' && game->map.grid[my][mx] != '3'
				&& check_wallhack_backward(game))
			{
				game->player_x -= game->player_deltax / game->sprint_mult;
				game->player_y -= game->player_deltay / game->sprint_mult;
			}
		}
	}
}

void	go_forward(t_game *game)
{
	int	mx;
	int	my;

	mx = (int)(game->player_x + (game->player_deltax * 2))
		/ game->pix;
	my = (int)(game->player_y + (game->player_deltay * 2))
		/ game->pix;
	if (mx < game->map.grid_height && mx > 0)
	{
		if (my < game->map.grid_height && my > 0)
		{
			if (game->map.grid[my][mx] != '1' && game->map.grid[my][mx] != '3'
				&& check_wallhack(game))
			{
				game->player_x += game->player_deltax / game->sprint_mult;
				game->player_y += game->player_deltay / game->sprint_mult;
			}
		}
	}
}

void	strafe_left(t_game *game)
{
	int	mx;
	int	my;

	mx = (int)(game->player_x - (game->strafe_deltax * 2))
		/ game->pix;
	my = (int)(game->player_y - (game->strafe_deltay * 2))
		/ game->pix;
	if (mx < game->map.grid_height && mx > 0)
	{
		if (my < game->map.grid_height && my > 0)
		{
			if (game->map.grid[my][mx] != '1' && game->map.grid[my][mx] != '3'
				&& check_wallhack_strafe_l(game))
			{
				game->player_x -= game->strafe_deltax / game->sprint_mult;
				game->player_y -= game->strafe_deltay / game->sprint_mult;
			}
		}
	}
}

void	strafe_right(t_game *game)
{
	int	mx;
	int	my;

	mx = (int)(game->player_x + (game->strafe_deltax * 2))
		/ game->pix;
	my = (int)(game->player_y + (game->strafe_deltay * 2))
		/ game->pix;
	if (mx < game->map.grid_height && mx > 0)
	{
		if (my < game->map.grid_height && my > 0)
		{
			if (game->map.grid[my][mx] != '1' && game->map.grid[my][mx] != '3'
				&& check_wallhack_strafe_r(game))
			{
				game->player_x += game->strafe_deltax / game->sprint_mult;
				game->player_y += game->strafe_deltay / game->sprint_mult;
			}
		}
	}
}

void	move_player(t_game *game)
{
	if (game->forwd == 1)
		go_forward(game);
	if (game->backwd == 1)
		go_backward(game);
	if (game->look_l == 1)
		turn_left(game);
	if (game->look_r == 1)
		turn_right(game);
	if (game->strafe_l == 1)
		strafe_left(game);
	if (game->strafe_r)
		strafe_right(game);
}
