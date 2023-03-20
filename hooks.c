/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-youb <ael-youb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:04:14 by ael-youb          #+#    #+#             */
/*   Updated: 2023/03/20 15:49:29 by ael-youb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	destroy_window(t_game *game)
{
	close_program(game);
	return (1);
}

int	hook_slide(int keycode, t_game *game)
{
	if (keycode == 65361) // left
	{
		game->player_angle -= 0.1;
		if (game->player_angle < 0)
			game->player_angle+= 2*PI;
		game->player_deltax = cos(game->player_angle) * 5;
		game->player_deltay = sin(game->player_angle) * 5;
	}
	else if (keycode == 65363) //right
	{
		game->player_angle += 0.1;
		if (game->player_angle > 2*PI)
			game->player_angle-= 2*PI;
		game->player_deltax = cos(game->player_angle) * 5;
		game->player_deltay = sin(game->player_angle) * 5;
	}
	else if (keycode == 65364)
	{
		game->player_x -= game->player_deltax;
		game->player_y -= game->player_deltay;
	}
	else if (keycode == 65362)
	{
		game->player_x += game->player_deltax;
		game->player_y += game->player_deltay;
	}
	add_to_image(game);
	return (keycode);
}

void	close_program(t_game *game)
{
	//NB: CLEAN LA MAP ici
	mlx_destroy_window(game->win->mlx, game->win->mlx_win);
	mlx_destroy_image(game->win->mlx, game->img->img);
	mlx_destroy_display(game->win->mlx);
	free(game->win->mlx);
	free(game->store);
	free_map(&game->map);
	//free(game);

	exit(1);
}
