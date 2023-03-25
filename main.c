/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-youb <ael-youb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:03:34 by tgrasset          #+#    #+#             */
/*   Updated: 2023/03/25 22:45:39 by ael-youb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	select_player_dir(t_game *game)
{
	if (game->map.p_dir == 'N')
		game->player_angle = P3;
	if (game->map.p_dir == 'S')
		game->player_angle = P2;
	if (game->map.p_dir == 'E')
		game->player_angle = 0;
	if (game->map.p_dir == 'O')
		game->player_angle = PI;
}

int	main(int ac, char **av)
{
	t_game	game;

	parse_cub_file(ac, av[1], &game.map);
	game.player_y = 512 / game.map.grid_height * game.map.p_y;
	game.player_x = 512 / game.map.grid_height * game.map.p_x;
	game.store.dof_max = game.map.grid_height - 1;
	printf("%d\n", game.store.dof_max);
	select_player_dir(&game);
	game.player_deltax = cos(game.player_angle) * 5;
	game.player_deltay = sin(game.player_angle) * 5;
	game.backwd = 0;
	game.forwd = 0;
	game.strafe_l = 0;
	game.strafe_r = 0;
	game.look_l = 0;
	game.look_r = 0;
	init_mlx(&game);
	close_program(&game);
	return (0);
}
