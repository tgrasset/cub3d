/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-youb <ael-youb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:03:34 by tgrasset          #+#    #+#             */
/*   Updated: 2023/03/14 16:11:00 by ael-youb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_game	*game;
	(void)av;
	(void)ac;

	game = (t_game *) malloc(sizeof(t_game) * 1);
  game->player_x = 300;
  game->player_y = 300;
  game->player_angle = 0.1;

	init_mlx(game);
	return (0);
}
