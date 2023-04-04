/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_distance_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-youb <ael-youb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:37:37 by tgrasset          #+#    #+#             */
/*   Updated: 2023/04/04 17:02:43 by ael-youb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	ray_special_case(t_game *game)
{
	game->store.rx = game->player_x;
	game->store.ry = game->player_y;
	game->store.dof = game->store.dof_max;
}

int	is_wall_or_door(t_game *game)
{
	if ((game->map.grid[game->store.my][game->store.mx] == '1'
		|| game->map.grid[game->store.my][game->store.mx] == '3'))
		return (1);
	return (0);
}
