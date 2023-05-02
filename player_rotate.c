/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-youb <ael-youb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:54:50 by tgrasset          #+#    #+#             */
/*   Updated: 2023/05/02 14:15:20 by ael-youb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	turn_left(t_game *game)
{
	game->player_angle -= ((DR / game->scale_ray) * 30);
	game->strafe_angle -= ((DR / game->scale_ray) * 30);
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
	game->player_angle += ((DR / game->scale_ray) * 30);
	game->strafe_angle += ((DR / game->scale_ray) * 30);
	if (game->player_angle > 2 * PI)
		game->player_angle -= 2 * PI;
	if (game->strafe_angle > 2 * PI)
		game->strafe_angle -= 2 * PI;
	game->player_deltax = cos(game->player_angle) * 5;
	game->player_deltay = sin(game->player_angle) * 5;
	game->strafe_deltax = cos(game->strafe_angle) * 5;
	game->strafe_deltay = sin(game->strafe_angle) * 5;
}

void	turn_right_mouse(t_game *game)
{
	game->player_angle += ((DR / game->scale_ray) * 110);
	game->strafe_angle += ((DR / game->scale_ray) * 110);
	if (game->player_angle > 2 * PI)
		game->player_angle -= 2 * PI;
	if (game->strafe_angle > 2 * PI)
		game->strafe_angle -= 2 * PI;
	game->player_deltax = cos(game->player_angle) * 5;
	game->player_deltay = sin(game->player_angle) * 5;
	game->strafe_deltax = cos(game->strafe_angle) * 5;
	game->strafe_deltay = sin(game->strafe_angle) * 5;
}

void	turn_left_mouse(t_game *game)
{
	game->player_angle -= ((DR / game->scale_ray) * 110);
	game->strafe_angle -= ((DR / game->scale_ray) * 110);
	if (game->player_angle < 0)
		game->player_angle += 2 * PI;
	if (game->strafe_angle < 0)
		game->strafe_angle += 2 * PI;
	game->player_deltax = cos(game->player_angle) * 5;
	game->player_deltay = sin(game->player_angle) * 5;
	game->strafe_deltax = cos(game->strafe_angle) * 5;
	game->strafe_deltay = sin(game->strafe_angle) * 5;
}
