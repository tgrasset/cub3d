/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_more_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-youb <ael-youb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 09:05:53 by ael-youb          #+#    #+#             */
/*   Updated: 2023/04/03 15:26:53 by ael-youb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_minimap(t_minimap *minimap, t_game *game)
{
	minimap->cases = (game->map.grid_height / 6);
	if (minimap->cases < 2)
		minimap->cases++;
	minimap->x = (int)(game->player_x) / game->pix;
	minimap->y = (int)(game->player_y) / game->pix;
	minimap->x = minimap->x - minimap->cases;
	minimap->y = minimap->y - minimap->cases;
	minimap->x_origin = 0;
	minimap->y_origin = 0;
	minimap->pix = game->pix / 2;
	if (minimap->pix > 50)
		minimap->pix = 50;
}

void	loop_minimap(t_game *game, t_minimap *minimap)
{
	while (minimap->xo < ((minimap->x_origin + 1) * minimap->pix))
	{
		while (minimap->yo < ((minimap->y_origin + 1) * minimap->pix))
		{
			if (minimap->x < 0 || minimap->x >= game->map.grid_height)
				break ;
			if (minimap->y < 0 || minimap->y >= game->map.grid_height)
				break ;
			pixel_put(game->img, minimap->yo, minimap->xo,
				0x00000000);
			if (game->map.grid[minimap->y][minimap->x] == '1')
				pixel_put(game->img, minimap->yo, minimap->xo,
					0x88800000);
			else
				pixel_put(game->img, minimap->yo, minimap->xo,
					0x99999999);
			minimap->yo++;
		}
		minimap->yo = minimap->y_origin * minimap->pix;
		minimap->xo++;
	}
}

void	background_minimap(t_game *game, t_minimap *minimap)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < minimap->pix * minimap->cases * 2)
	{
		while (j < minimap->pix * minimap->cases * 2)
		{
			pixel_put(game->img, j, i,
				0x00000000);
			j++;
		}
		j = 0;
		i++;
	}
}

void	draw_map(t_game *game)
{
	t_minimap	minimap;

	init_minimap(&minimap, game);
	background_minimap(game, &minimap);
	while (minimap.x < (int)(game->player_x)
		/ minimap.pix + minimap.cases)
	{
		while (minimap.y < (int)(game->player_y) /
			minimap.pix + minimap.cases)
		{
			minimap.xo = minimap.x_origin * minimap.pix;
			minimap.yo = minimap.y_origin * minimap.pix;
			loop_minimap(game, &minimap);
			minimap.y++;
			minimap.y_origin++;
		}
		minimap.x++;
		minimap.x_origin++;
		minimap.y_origin = 0;
		minimap.y = (int)(game->player_y) / game->pix;
		minimap.y = minimap.y - minimap.cases;
	}
}

void	load_textures(t_game *game)
{
	game->north.img = mlx_xpm_file_to_image(game->win->mlx, game->map.north,
			&game->north.w, &game->north.h);
	game->south.img = mlx_xpm_file_to_image(game->win->mlx, game->map.south,
			&game->south.w, &game->south.h);
	game->east.img = mlx_xpm_file_to_image(game->win->mlx, game->map.east,
			&game->east.w, &game->east.h);
	game->west.img = mlx_xpm_file_to_image(game->win->mlx, game->map.west,
			&game->west.w, &game->west.h);
	game->sp_1.img = mlx_xpm_file_to_image(game->win->mlx, "./textures/slime1.xpm",
			&game->sp_1.w, &game->sp_1.h);
	game->sp_2.img = mlx_xpm_file_to_image(game->win->mlx, "./textures/slime2.xpm",
			&game->sp_2.w, &game->sp_2.h);
	game->sp_3.img = mlx_xpm_file_to_image(game->win->mlx, "./textures/slime3.xpm",
			&game->sp_3.w, &game->sp_3.h);
	game->sp_4.img = mlx_xpm_file_to_image(game->win->mlx, "./textures/slime4.xpm",
			&game->sp_4.w, &game->sp_4.h);
	game->sp_5.img = mlx_xpm_file_to_image(game->win->mlx, "./textures/slime5.xpm",
			&game->sp_5.w, &game->sp_5.h);
	game->sp_6.img = mlx_xpm_file_to_image(game->win->mlx, "./textures/slime6.xpm",
			&game->sp_6.w, &game->sp_6.h);
	if (game->north.img == NULL || game->south.img == NULL
		|| game->east.img == NULL || game->west.img == NULL
		|| game->sp_1.img == NULL || game->sp_2.img == NULL
		|| game->sp_3.img == NULL || game->sp_4.img == NULL
		|| game->sp_5.img == NULL || game->sp_6.img == NULL)
	{
		ft_putendl_fd("Error\nTextures couldn't be loaded", 2);
		close_program(game);
	}
	game->north.addr = mlx_get_data_addr(game->north.img, &game->north.bpp,
			&game->north.ll, &game->north.endian);
	game->south.addr = mlx_get_data_addr(game->south.img, &game->south.bpp,
			&game->south.ll, &game->south.endian);
	game->east.addr = mlx_get_data_addr(game->east.img, &game->east.bpp,
			&game->east.ll, &game->east.endian);
	game->west.addr = mlx_get_data_addr(game->west.img, &game->west.bpp,
			&game->west.ll, &game->west.endian);
	game->sp_1.addr = mlx_get_data_addr(game->sp_1.img, &game->sp_1.bpp,
			&game->sp_1.ll, &game->sp_1.endian);
	game->sp_2.addr = mlx_get_data_addr(game->sp_2.img, &game->sp_2.bpp,
			&game->sp_2.ll, &game->sp_2.endian);
	game->sp_3.addr = mlx_get_data_addr(game->sp_3.img, &game->sp_3.bpp,
			&game->sp_3.ll, &game->sp_3.endian);
	game->sp_4.addr = mlx_get_data_addr(game->sp_4.img, &game->sp_4.bpp,
			&game->sp_4.ll, &game->sp_4.endian);
	game->sp_5.addr = mlx_get_data_addr(game->sp_5.img, &game->sp_5.bpp,
			&game->sp_5.ll, &game->sp_5.endian);
	game->sp_6.addr = mlx_get_data_addr(game->sp_6.img, &game->sp_6.bpp,
			&game->sp_6.ll, &game->sp_6.endian);
}

void	draw_player(t_game *game)
{
	int	i;
	int	j;
	int	cases;
	int	pix;

	cases = (game->map.grid_height / 6) * 2;
	if (game->map.grid_height > 2 && cases < 2)
		cases++;
	pix = game->pix / 2;
	if (pix > 40)
		pix = 40;
	i = cases * pix + (pix);
	j = cases * pix + (pix);
	while (i < (cases * pix + (pix)) + 4)
	{
		while (j < (cases * pix + (pix)) + 4)
		{
			pixel_put(game->img, i, j,
				0x80090888);
			j++;
		}
		j = cases * pix + (pix);
		i++;
	}
	util_draw_player(game, cases, pix);
}
