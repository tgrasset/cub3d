/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrasset <tgrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:04:14 by ael-youb          #+#    #+#             */
/*   Updated: 2023/04/05 12:28:25 by tgrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	open_close_door(t_game *game)
{
	int	mx;
	int	my;

	mx = (int)game->player_x / game->pix;
	my = (int)game->player_y / game->pix;
	if (mx > 0 && game->map.grid[my][mx - 1] == '3')
		game->map.grid[my][mx - 1] = '4';
	else if (my > 0 && game->map.grid[my - 1][mx] == '3')
		game->map.grid[my - 1][mx] = '4';
	else if (my < game->map.grid_height - 1
		&& game->map.grid[my + 1][mx] == '3')
		game->map.grid[my + 1][mx] = '4';
	else if (mx < game->map.grid_height - 1
		&& game->map.grid[my][mx + 1] == '3')
		game->map.grid[my][mx + 1] = '4';
	else if (mx > 0 && game->map.grid[my][mx - 1] == '4')
		game->map.grid[my][mx - 1] = '3';
	else if (my > 0 && game->map.grid[my - 1][mx] == '4')
		game->map.grid[my - 1][mx] = '3';
	else if (my < game->map.grid_height - 1
		&& game->map.grid[my + 1][mx] == '4')
		game->map.grid[my + 1][mx] = '3';
	else if (mx < game->map.grid_height - 1
		&& game->map.grid[my][mx + 1] == '4')
		game->map.grid[my][mx + 1] = '3';
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
	if (keycode == 65505)
		game->sprint_mult = 2;
	if (keycode && keycode != XK_Left && keycode != XK_Right
		&& keycode != XK_Down && keycode != XK_s && keycode != XK_Up
		&& keycode != XK_w && keycode != XK_d && keycode != XK_a
		&& keycode != XK_Escape && keycode != 65505 && keycode != 32)
		game->focus = 0;
	if (keycode == 32)
		open_close_door(game);
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
	if (keycode == 65505)
		game->sprint_mult = 4;
	return (0);
}

void	close_program_2(t_game *game)
{
	if (game->door.img != NULL)
		mlx_destroy_image(game->win->mlx, game->door.img);
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
	exit(0);
}

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
	close_program_2(game);
	return (0);
}
