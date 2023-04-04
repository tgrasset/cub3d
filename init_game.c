/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrasset <tgrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:53:57 by ael-youb          #+#    #+#             */
/*   Updated: 2023/04/04 14:46:43 by tgrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_if_loaded(t_game *game)
{
	if (game->north.img == NULL || game->south.img == NULL
		|| game->east.img == NULL || game->west.img == NULL
		|| game->sp_1.img == NULL || game->sp_2.img == NULL
		|| game->sp_3.img == NULL || game->sp_4.img == NULL
		|| game->sp_5.img == NULL || game->sp_6.img == NULL
		|| game->door.img == NULL)
	{
		ft_putendl_fd("Error\nTextures couldn't be loaded", 2);
		close_program(game);
	}
}

void	textures_get_data_addr(t_game *game)
{
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
	game->door.addr = mlx_get_data_addr(game->door.img, &game->door.bpp,
			&game->door.ll, &game->door.endian);
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
	game->sp_1.img = mlx_xpm_file_to_image(game->win->mlx, "./textures/s1.xpm",
			&game->sp_1.w, &game->sp_1.h);
	game->sp_2.img = mlx_xpm_file_to_image(game->win->mlx, "./textures/s2.xpm",
			&game->sp_2.w, &game->sp_2.h);
	game->sp_3.img = mlx_xpm_file_to_image(game->win->mlx, "./textures/s3.xpm",
			&game->sp_3.w, &game->sp_3.h);
	game->sp_4.img = mlx_xpm_file_to_image(game->win->mlx, "./textures/s4.xpm",
			&game->sp_4.w, &game->sp_4.h);
	game->sp_5.img = mlx_xpm_file_to_image(game->win->mlx, "./textures/s5.xpm",
			&game->sp_5.w, &game->sp_5.h);
	game->sp_6.img = mlx_xpm_file_to_image(game->win->mlx, "./textures/s6.xpm",
			&game->sp_6.w, &game->sp_6.h);
	game->door.img = mlx_xpm_file_to_image(game->win->mlx, "./textures/dr.xpm",
			&game->door.w, &game->door.h);
	check_if_loaded(game);
	textures_get_data_addr(game);
}

int	render(t_game *game)
{
	if (game->frame >= LOOP)
		game->frame = 0;
	if (game->focus == 1)
		check_mouse_move(game);
	move_player(game);
	draw_rays(game);
	if (game->map.sprite_nb != 0)
		draw_sprites(game, -1);
	draw_map(game);
	draw_player(game);
	mlx_put_image_to_window(game->win->mlx,
		game->win->mlx_win, game->img->img, 0, 0);
	game->frame++;
	return (0);
}

void	init_mlx(t_game *game)
{
	t_vars	win;
	t_data	img;

	win.mlx = mlx_init();
	win.mlx_win = mlx_new_window(win.mlx, RAY_NUMBER, HEIGHT, "Louveteau 3D");
	img.img = mlx_new_image(win.mlx, RAY_NUMBER, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.ll, &img.endian);
	game->win = &win;
	game->img = &img;
	load_textures(game);
	render(game);
	mlx_hook(game->win->mlx_win, 4, 1L << 2, capture_mouse, game);
	mlx_hook(win.mlx_win, 17, 0L, close_program, game);
	mlx_hook(win.mlx_win, 2, 1L << 0, key_press, game);
	mlx_loop_hook(win.mlx, render, game);
	mlx_hook(win.mlx_win, 3, 1L << 1, key_release, game);
	mlx_loop(win.mlx);
}
