/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrasset <tgrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:04:14 by ael-youb          #+#    #+#             */
/*   Updated: 2023/03/30 18:00:32 by tgrasset         ###   ########.fr       */
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
	if (game->sp_1.img != NULL)
		mlx_destroy_image(game->win->mlx, game->sp_1.img);
	if (game->sp_2.img != NULL)
		mlx_destroy_image(game->win->mlx, game->sp_2.img);
	if (game->sp_3.img != NULL)
		mlx_destroy_image(game->win->mlx, game->sp_3.img);
	if (game->sp_4.img != NULL)
		mlx_destroy_image(game->win->mlx, game->sp_4.img);
	if (game->sp_5.img != NULL)
		mlx_destroy_image(game->win->mlx, game->sp_5.img);
	if (game->sp_6.img != NULL)
		mlx_destroy_image(game->win->mlx, game->sp_6.img);
	if (game->sprites.dist != NULL)
		free(game->sprites.dist);
	if (game->sprites.order != NULL)
		free(game->sprites.order);
	if (game->sprites.sp_x != NULL)
		free(game->sprites.sp_x);
	if (game->sprites.sp_y != NULL)
		free(game->sprites.sp_y);
	mlx_destroy_display(game->win->mlx);
	free(game->win->mlx);
	free_map(&game->map);
	exit(1);
}

void	turn_left(t_game *game)
{
	game->player_angle -= 0.05;
	game->strafe_angle -= 0.05;
	if (game->player_angle < 0)
		game->player_angle += 2 * PI;
	if (game->strafe_angle < 0)
		game->strafe_angle += 2 * PI;
	game->player_deltax = cos(game->player_angle) * 5;
	game->player_deltay = sin(game->player_angle) * 5;
	game->strafe_deltax = cos(game->strafe_angle) * 5;
	game->strafe_deltay = sin(game->strafe_angle) * 5;
}

void	turn_right(t_game *game)
{
	game->player_angle += 0.05;
	game->strafe_angle += 0.05;
	if (game->player_angle > 2 * PI)
		game->player_angle -= 2 * PI;
	if (game->strafe_angle > 2 * PI)
		game->strafe_angle -= 2 * PI;
	game->player_deltax = cos(game->player_angle) * 5;
	game->player_deltay = sin(game->player_angle) * 5;
	game->strafe_deltax = cos(game->strafe_angle) * 5;
	game->strafe_deltay = sin(game->strafe_angle) * 5;
}

void	go_backward(t_game *game)
{
	int	mx;
	int	my;

	mx = (int)(game->player_x - (game->player_deltax * 2))
		/ (HEIGHT / game->map.grid_height);
	my = (int)(game->player_y - (game->player_deltay * 2))
		/ (HEIGHT / game->map.grid_height);
	if (mx < game->map.grid_height && mx > 0)
	{
		if (my < game->map.grid_height && my > 0)
		{
			if (game->map.grid[my][mx] == '0')
			{
				game->player_x -= game->player_deltax / 2;
				game->player_y -= game->player_deltay / 2;
			}
		}
	}
}

void	go_forward(t_game *game)
{
	int	mx;
	int	my;

	mx = (int)(game->player_x + (game->player_deltax * 2))
		/ (HEIGHT / game->map.grid_height);
	my = (int)(game->player_y + (game->player_deltay * 2))
		/ (HEIGHT / game->map.grid_height);
	if (mx < game->map.grid_height && mx > 0)
	{
		if (my < game->map.grid_height && my > 0)
		{
			if (game->map.grid[my][mx] == '0')
			{
				game->player_x += game->player_deltax / 2;
				game->player_y += game->player_deltay / 2;
			}
		}
	}
}
