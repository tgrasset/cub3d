/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-youb <ael-youb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:25:35 by tgrasset          #+#    #+#             */
/*   Updated: 2023/04/03 15:08:50 by ael-youb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	capture_mouse(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	(void)button;
	if (game->focus == 0)
		game->focus = 1;
	else
		game->focus = 0;
	return (0);
}

void	check_mouse_move(t_game *game)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(game->win->mlx, game->win->mlx_win, &x, &y);
	mlx_mouse_move(game->win->mlx, game->win->mlx_win, RAY_NUMBER / 2, 0);
	if (x > RAY_NUMBER / 2)
		turn_right(game);
	if (x < RAY_NUMBER / 2)
		turn_left(game);
}
