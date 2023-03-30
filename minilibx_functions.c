/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-youb <ael-youb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:53:57 by ael-youb          #+#    #+#             */
/*   Updated: 2023/03/30 02:26:45 by ael-youb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (x * data->ll + y * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	loop_draw_three_d(t_game *game, float height, float offset)
{
	int		j;

	j = 0;
	while (j < offset)
	{
		pixel_put(game->img, j, (game->store.r),
			game->map.ceiling_int);
			j++;
	}
	loop_loop_drawthreed(game, height, offset, j);
	j = height + offset;
	while (j <= HEIGHT)
	{
		pixel_put(game->img, j, (game->store.r),
			game->map.floor_int);
			j++;
	}
}

void	draw_three_d(t_game *game, float distance, float ra)
{
	float	height;
	float	offset;
	float	plan_fisheye;

	plan_fisheye = game->player_angle - ra;
	if (plan_fisheye < 0)
		plan_fisheye += 2 * PI;
	if (plan_fisheye > 2 * PI)
		plan_fisheye -= 2 * PI;
	distance = distance * cos(plan_fisheye);
	height = (32 * HEIGHT) / distance;
	game->store.actual_height = height;
	if (height > HEIGHT)
		height = HEIGHT;
	offset = (HEIGHT / 2) - height / 2;
	loop_draw_three_d(game, height, offset);
}

int	render(t_game *game)
{
	float	i;
	float	j;

	i = 0;
	j = 0;
	while (i < HEIGHT)
	{
		while (j < RAY_NUMBER)
		{
			pixel_put(game->img, i, j,
				0x80808080);
			j++;
		}
		j = 0;
		i++;
	}
	move_player(game);
	draw_rays(game);
	draw_map(game);
	draw_player(game);
	mlx_put_image_to_window(game->win->mlx,
		game->win->mlx_win, game->img->img, 0, 0);
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
	mlx_hook(win.mlx_win, 17, 0L, close_program, game);
	mlx_hook(win.mlx_win, 2, 1L << 0, key_press, game);
	mlx_loop_hook(win.mlx, render, game);
	mlx_hook(win.mlx_win, 3, 1L << 1, key_release, game);
	mlx_loop(win.mlx);
}
