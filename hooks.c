/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-youb <ael-youb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:04:14 by ael-youb          #+#    #+#             */
/*   Updated: 2023/03/25 23:02:37 by ael-youb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_program(t_game *game)
{
	mlx_destroy_window(game->win->mlx, game->win->mlx_win);
	mlx_destroy_image(game->win->mlx, game->img->img);
	if (game->north.img != NULL)
		mlx_destroy_image(game->win->mlx, game->north.img);
	if (game->south.img != NULL)
		mlx_destroy_image(game->win->mlx, game->south.img);
	if (game->east.img != NULL)
		mlx_destroy_image(game->win->mlx, game->east.img);
	if (game->west.img != NULL)
		mlx_destroy_image(game->win->mlx, game->west.img);
	mlx_destroy_display(game->win->mlx);
	free(game->win->mlx);
	free_map(&game->map);
	//free(game);
	exit(1);
}

void	turn_left(t_game *game)
{
	game->player_angle -= 0.015;
	if (game->player_angle < 0)
		game->player_angle+= 2*PI;
	game->player_deltax = cos(game->player_angle) * 5;
	game->player_deltay = sin(game->player_angle) * 5;
}

void	turn_right(t_game *game)
{
	game->player_angle += 0.015;
	if (game->player_angle > 2*PI)
		game->player_angle-= 2*PI;
	game->player_deltax = cos(game->player_angle) * 5;
	game->player_deltay = sin(game->player_angle) * 5;
}

void	go_backward(t_game *game)
{
	int	mx;
	int	my;

	mx = (int)(game->player_x - (game->player_deltax * 2)) / (512 / game->map.grid_height);
	my = (int)(game->player_y - (game->player_deltay * 2)) / (512 / game->map.grid_height);
	if (mx < game->map.grid_height && mx > 0)
	{
		if (my < game->map.grid_height && my > 0)
		{
			if (game->map.grid[my][mx] == '0')
			{
				game->player_x -= game->player_deltax / 12;
				game->player_y -= game->player_deltay / 12;
			}
		}
	}
}

void	go_forward(t_game *game)
{
	int	mx;
	int	my;

	mx = (int)(game->player_x + (game->player_deltax * 2)) / (512 / game->map.grid_height);
	my = (int)(game->player_y + (game->player_deltay * 2)) / (512 / game->map.grid_height);
	if (mx < game->map.grid_height && mx > 0)
	{
		if (my < game->map.grid_height && my > 0)
		{
			if (game->map.grid[my][mx] == '0')
			{
				game->player_x += game->player_deltax / 12;
				game->player_y += game->player_deltay / 12;
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
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == XK_Left)
		game->look_l = 1;
	if (keycode == XK_Right)
		game->look_r = 1;
	if (keycode == XK_Down || keycode == XK_S)
		game->backwd = 1;
	if (keycode == XK_Up || keycode == XK_W)
		game->forwd = 1;
	if (keycode == XK_D)
		game->strafe_r = 1;
	if (keycode == 113)
		game->strafe_l = 1;
	if (keycode == XK_Escape)
		close_program(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == XK_Left)
		game->look_l = 0;
	if (keycode == XK_Right)
		game->look_r = 0;
	if (keycode == XK_Down || keycode == XK_S)
		game->backwd = 0;
	if (keycode == XK_Up || keycode == XK_W)
		game->forwd = 0;
	if (keycode == XK_D)
		game->strafe_r = 0;
	if (keycode == XK_A)
		game->strafe_l = 0;
	if (keycode == XK_Escape)
		close_program(game);
	return (0);
}
