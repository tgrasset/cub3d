/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrasset <tgrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 09:34:36 by ael-youb          #+#    #+#             */
/*   Updated: 2023/03/27 16:13:04 by tgrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	strafe_left(t_game *game)
{
	int	mx;
	int	my;

	mx = (int)(game->player_x - (game->strafe_deltax * 2))
		/ (HEIGHT / game->map.grid_height);
	my = (int)(game->player_y - (game->strafe_deltay * 2))
		/ (HEIGHT / game->map.grid_height);
	if (mx < game->map.grid_height && mx > 0)
	{
		if (my < game->map.grid_height && my > 0)
		{
			if (game->map.grid[my][mx] == '0')
			{
				game->player_x -= game->strafe_deltax / 4;
				game->player_y -= game->strafe_deltay / 4;
			}
		}
	}
}

void	strafe_right(t_game *game)
{
	int	mx;
	int	my;

	mx = (int)(game->player_x + (game->strafe_deltax * 2))
		/ (HEIGHT / game->map.grid_height);
	my = (int)(game->player_y + (game->strafe_deltay * 2))
		/ (HEIGHT / game->map.grid_height);
	if (mx < game->map.grid_height && mx > 0)
	{
		if (my < game->map.grid_height && my > 0)
		{
			if (game->map.grid[my][mx] == '0')
			{
				game->player_x += game->strafe_deltax / 4;
				game->player_y += game->strafe_deltay / 4;
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

int	key_press(int keycode, t_game *game)
{
	if (keycode == XK_Left)
		game->look_l = 1;
	if (keycode == XK_Right)
		game->look_r = 1;
	if (keycode == XK_Down || keycode == XK_s)
		game->backwd = 1;
	if (keycode == XK_Up || keycode == XK_w)
		game->forwd = 1;
	if (keycode == XK_d)
		game->strafe_r = 1;
	if (keycode == XK_a)
		game->strafe_l = 1;
	if (keycode == XK_Escape)
		close_program(game);
	if (keycode && keycode != XK_Left && keycode != XK_Right
		&& keycode != XK_Down && keycode != XK_s && keycode != XK_Up
		&& keycode != XK_w && keycode != XK_d && keycode != XK_a
		&& keycode != XK_Escape)
		game->focus = 0;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == XK_Left)
		game->look_l = 0;
	if (keycode == XK_Right)
		game->look_r = 0;
	if (keycode == XK_Down || keycode == XK_s)
		game->backwd = 0;
	if (keycode == XK_Up || keycode == XK_w)
		game->forwd = 0;
	if (keycode == XK_d)
		game->strafe_r = 0;
	if (keycode == XK_a)
		game->strafe_l = 0;
	return (0);
}
