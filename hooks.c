/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-youb <ael-youb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:04:14 by ael-youb          #+#    #+#             */
/*   Updated: 2023/03/14 15:19:13 by ael-youb         ###   ########.fr       */
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
	if (keycode == 65361)
	{
		game->player_x -= 5;
	}
	else if (keycode == 65363)
	{
		game->player_x += 5;
	}
	else if (keycode == 65364)
	{
		game->player_y += 5;
	}
	else if (keycode == 65362)
	{
		game->player_y -= 5;
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
	free(game);
	exit(1);
}
