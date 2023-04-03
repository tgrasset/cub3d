/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-youb <ael-youb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:16:51 by tgrasset          #+#    #+#             */
/*   Updated: 2023/04/03 15:08:52 by ael-youb         ###   ########.fr       */
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
				game->sprites.sp_x[k] = game->pix * (float)j;
				game->sprites.sp_y[k] = game->pix * (float)i;
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
		game->sprites.dist[i] = ((game->player_x - game->sprites.sp_x[i]) *
			(game->player_x - game->sprites.sp_x[i]) + (game->player_y -
			game->sprites.sp_y[i]) * (game->player_y - game->sprites.sp_y[i]));
		i++;
	}
	sort_sprites_from_furthest(game, 0, 0, 0);
}

int	get_sprite_colour(t_data *data, int width, int height, int x, int y)
{
	char			*dst;
	
	x = 14 * x / width;
	y = 23 * y / height;
	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	return (*(unsigned int *)dst);
}

int	choose_sprite(t_game *game, int width, int height, int x, int y)
{
	if (game->frame > 0 && game->frame <= LOOP / 6)
		return (get_sprite_colour(&game->sp_1, width, height, x, y));
	else if (game->frame > LOOP / 6 && game->frame <= 2 * (LOOP / 6))
		return (get_sprite_colour(&game->sp_2, width, height, x, y));
	else if (game->frame > 2 * (LOOP / 6) && game->frame <= 3 * (LOOP / 6))
		return (get_sprite_colour(&game->sp_3, width, height, x, y));
	else if (game->frame > 3 * (LOOP / 6) && game->frame <= 4 * (LOOP / 6))
		return (get_sprite_colour(&game->sp_4, width, height, x, y));
	else if (game->frame > 4 * (LOOP / 6) && game->frame <= 5 * (LOOP / 6))
		return (get_sprite_colour(&game->sp_5, width, height, x, y));
	else
		return (get_sprite_colour(&game->sp_6, width, height, x, y));
}

void	display_sprite(t_game *game, float sx, float sy, int i)
{
	int	width;
	int	height;
	int	j;
	int	k;
	int	colour;

	width =  300000 / game->sprites.dist[i];
	height = width * 23 / 14;
	j = (int)sx;
	while (j < (int)sx + width)
	{
		k = (int)sy;
		while (k < (int)sy + height)
		{
			colour = choose_sprite(game, width, height, j - (int)sx, k - (int)sy);
			if (j > 0 && j < RAY_NUMBER && k > 0 && k < HEIGHT && colour != 0x00FF2F)
				pixel_put(game->img, k, j, colour);
			k++;
		}
		j++;
	}
}

void	draw_sprites(t_game *game)
{
	int		i;
	float	cs;
	float	sn;
	float	sx;
	float	sy;
	float	sz;
	
	check_distance_and_sort(game, 0);
	i = 0;
	while (i < game->map.sprite_nb)
	{
		if (game->sprites.dist[i] < 1000)
		{
			i++;
			continue ;
		}
		game->sprites.rel_x = (game->sprites.sp_x[i] - game->player_x);
		game->sprites.rel_y = (game->sprites.sp_y[i] - game->player_y);
		sz = 10;
		cs = cos(game->player_angle);
		sn = sin(game->player_angle);
		sx = game->sprites.rel_y * cs - game->sprites.rel_x * sn;
		sy = game->sprites.rel_x * cs + game->sprites.rel_y * sn;
		sx = (sx * 900.0/sy) + (RAY_NUMBER/2);
		sy = (sz * 900.0/sy) + (HEIGHT/2);
		display_sprite(game, sx, sy, i);
		i++;
	}
}