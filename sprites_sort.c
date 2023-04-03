/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrasset <tgrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:49:18 by tgrasset          #+#    #+#             */
/*   Updated: 2023/04/03 18:32:17 by tgrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_sprite_struct(t_game *game, int i, int j, int k)
{
	game->sprites.order = malloc(sizeof(int) * game->map.sprite_nb);
	game->sprites.dist = malloc(sizeof(float) * game->map.sprite_nb);
	game->sprites.sp_x = malloc(sizeof(float) * game->map.sprite_nb);
	game->sprites.sp_y = malloc(sizeof(float) * game->map.sprite_nb);
	if (game->sprites.order == NULL || game->sprites.dist == NULL
		|| game->sprites.sp_x == NULL || game->sprites.sp_y == NULL)
	{
		ft_putendl_fd("Error\nMalloc couldn't allocate memory", 2);
		close_program(game);
	}
	while (game->map.grid[i] != NULL)
	{
		j = 0;
		while (game->map.grid[i][j] != '\0')
		{
			if (game->map.grid[i][j] == '2')
			{
				game->sprites.sp_x[k] = 30 * (float)j + 0.5;
				game->sprites.sp_y[k] = 30 * (float)i + 0.5;
				k++;
			}
			j++;
		}
		i++;
	}
}

void	sort_sprites_from_furthest(t_game *game, int i, int j, float tmp)
{
	while (i < game->map.sprite_nb)
	{
		j = i + 1;
		while (j < game->map.sprite_nb)
		{
			if (game->sprites.dist[j] > game->sprites.dist[i])
			{
				tmp = game->sprites.dist[j];
				game->sprites.dist[j] = game->sprites.dist[i];
				game->sprites.dist[i] = tmp;
				tmp = game->sprites.order[j];
				game->sprites.order[j] = game->sprites.order[i];
				game->sprites.order[i] = (int)tmp;
			}
			j++;
		}
		i++;
	}
}

void	check_distance_and_sort(t_game *game, int i)
{
	while (i < game->map.sprite_nb)
	{
		game->sprites.order[i] = i;
		game->sprites.dist[i] = ((game->player_x - game->sprites.sp_x[i])
				* (game->player_x - game->sprites.sp_x[i]) + (game->player_y
					- game->sprites.sp_y[i])
				* (game->player_y - game->sprites.sp_y[i]));
		i++;
	}
	sort_sprites_from_furthest(game, 0, 0, 0);
}
