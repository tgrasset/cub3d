/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_secure_utils_left.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrasset <tgrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:58:16 by tgrasset          #+#    #+#             */
/*   Updated: 2023/04/03 17:47:26 by tgrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_angle_leftx_s(t_game *game)
{
	float	angle;

	angle = game->strafe_angle - (20 * DR);
	if (angle < 0)
		angle += 2 * PI;
	if (angle < 0)
		angle += 2 * PI;
	return (cos(angle) * 5);
}

int	check_angle_lefty_s(t_game *game)
{
	float	angle;

	angle = game->strafe_angle - (20 * DR);
	if (angle < 0)
		angle += 2 * PI;
	if (angle < 0)
		angle += 2 * PI;
	return (sin(angle) * 5);
}

int	check_angle_leftx(t_game *game)
{
	float	angle;

	angle = game->player_angle - (30 * DR);
	if (angle < 0)
		angle += 2 * PI;
	if (angle < 0)
		angle += 2 * PI;
	return (cos(angle) * 5);
}

int	check_angle_lefty(t_game *game)
{
	float	angle;

	angle = game->player_angle - (30 * DR);
	if (angle < 0)
		angle += 2 * PI;
	if (angle < 0)
		angle += 2 * PI;
	return (sin(angle) * 5);
}
