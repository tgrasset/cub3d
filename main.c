/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrasset <tgrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:03:34 by tgrasset          #+#    #+#             */
/*   Updated: 2023/03/27 15:21:49 by tgrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	select_player_dir(t_game *game)
{
	if (game->map.p_dir == 'N')
	{
		game->strafe_angle = 0;
		game->player_angle = P3;
	}
	if (game->map.p_dir == 'S')
	{
		game->strafe_angle = PI;
		game->player_angle = P2;
	}
	if (game->map.p_dir == 'E')
	{
		game->strafe_angle = P2;
		game->player_angle = 0;
	}
	if (game->map.p_dir == 'W')
	{
		game->strafe_angle = P3;
		game->player_angle = PI;
	}
}

void	ceiling_floor_colors(t_game *game)
{
	game->map.floor_int = rgb(game->map.floor[0],
			game->map.floor[1], game->map.floor[2]);
	game->map.ceiling_int = rgb(game->map.ceiling[0],
			game->map.ceiling[1], game->map.ceiling[2]);
}

int	main(int ac, char **av)
{
	t_game	game;

	parse_cub_file(ac, av[1], &game.map);
	game.player_y = HEIGHT / game.map.grid_height * game.map.p_y;
	game.player_x = HEIGHT / game.map.grid_height * game.map.p_x;
	game.store.dof_max = game.map.grid_height - 1;
	select_player_dir(&game);
	ceiling_floor_colors(&game);
	game.player_deltax = cos(game.player_angle) * 5;
	game.player_deltay = sin(game.player_angle) * 5;
	game.strafe_deltax = cos(game.strafe_angle) * 5;
	game.strafe_deltay = sin(game.strafe_angle) * 5;
	game.backwd = 0;
	game.forwd = 0;
	game.strafe_l = 0;
	game.strafe_r = 0;
	game.look_l = 0;
	game.look_r = 0;
	game.focus = 0;
	init_mlx(&game);
	close_program(&game);
	return (0);
}
