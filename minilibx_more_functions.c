/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_more_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-youb <ael-youb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 09:05:53 by ael-youb          #+#    #+#             */
/*   Updated: 2023/03/27 09:23:09 by ael-youb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_minimap(t_minimap *minimap, t_game *game)
{
	minimap->cases = (game->map.grid_height / 6);
	if (minimap->cases < 2)
		minimap->cases++;
	minimap->x = (int)(game->player_x) / (512 / game->map.grid_height);
	minimap->y = (int)(game->player_y) / (512 / game->map.grid_height);
	minimap->x = minimap->x - minimap->cases;
	minimap->y = minimap->y - minimap->cases;
	minimap->x_origin = 0;
	minimap->y_origin = 0;
	minimap->pix = 512 / (game->map.grid_width);
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

void	draw_map(t_game *game)
{
	t_minimap	minimap;

	init_minimap(&minimap, game);
	while (minimap.x < (int)(game->player_x)
		/ (512 / game->map.grid_height) + minimap.cases)
	{
		while (minimap.y < (int)(game->player_y) /
			(512 / game->map.grid_height) + minimap.cases)
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
		minimap.y = (int)(game->player_y) / (512 / game->map.grid_height);
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
	if (game->north.img == NULL || game->south.img == NULL
		|| game->east.img == NULL || game->west.img == NULL)
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
}

void	draw_player(t_game *game)
{
	int	i;
	int	j;
	int	cases;
	int	pix;

	cases = (game->map.grid_height / 6) * 2;
	if (game->map.grid_height > 2 && cases / 2 < 2)
		cases += 2;
	pix = 512 / (game->map.grid_height * 2);
	if (pix > 50)
		pix = 50;
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
