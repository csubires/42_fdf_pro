/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/07/30 12:09:00 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	initialise_mlx(t_fdfs *fdfs)
{
	mlx_set_setting(MLX_MAXIMIZED, MAXIMIZED);
	if (!(fdfs->mlx = mlx_init(WIN_W, WIN_H, "FDF PRO - CSUBIRES", true)))
		error_and_exit("initialise_mlx", "mlx_init");

	if (!(fdfs->img = mlx_new_image(fdfs->mlx, WIN_W, WIN_H)))
		error_and_exit("initialise_mlx", "mlx_image_t");

	if (!(fdfs->menu = mlx_new_image(fdfs->mlx, MENU_W, MENU_H)))
		error_and_exit("initialise_mlx", "mlx_image_t");

	if (mlx_image_to_window(fdfs->mlx, fdfs->img, 0, 0) < 0)
		error_and_exit("initialise_mlx", "mlx_image_to_window");
	reset_fdfs(fdfs);
	render_menu(fdfs);
	render_map(fdfs);
	if (mlx_image_to_window(fdfs->mlx, fdfs->menu, (WIN_W - MENU_W) / 2, (WIN_H - MENU_H) / 2) < 0)
			error_and_exit("initialise_mlx", "mlx_image_to_window");
}

int	main(int argc, char *argv[])
{
	t_map	*map;
	t_fdfs	*fdfs;

	map = 0;
	srand(time(0));
	parse_args(&map, argc, argv);
	if (!(fdfs = (t_fdfs *)malloc(sizeof(t_fdfs))))
		error_and_exit("initialise_mlx", "initialise_fdfs or malloc");
	fdfs->map = map;
	initialise_mlx(fdfs);
	mlx_loop_hook(fdfs->mlx, zoom_and_altitude, fdfs);
	mlx_loop_hook(fdfs->mlx, move, fdfs);
	mlx_loop_hook(fdfs->mlx, rotation, fdfs);
	mlx_key_hook(fdfs->mlx, key_hook, fdfs);
	mlx_mouse_hook(fdfs->mlx, mouse_hook, fdfs);
	mlx_loop(fdfs->mlx);
	mlx_terminate(fdfs->mlx);
	//free_all(fdfs);
	return (0);
}
