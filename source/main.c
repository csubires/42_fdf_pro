/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/08/09 13:35:36 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	initialise_mlx(t_fdfs *fdfs)
{
	int width;
	int height;

	mlx_set_setting(MLX_MAXIMIZED, MAXIMIZED);
	mlx_set_setting(MLX_DECORATED, DECORATED);

	if (!(fdfs->mlx = mlx_init(WIN_W, WIN_H, "FDF PRO - CSUBIRES", true)))
		error_and_exit("initialise_mlx", "mlx_init");

	if (!(fdfs->img = mlx_new_image(fdfs->mlx, WIN_W, WIN_H)))
		error_and_exit("initialise_mlx", "mlx_image_t");

	if (mlx_image_to_window(fdfs->mlx, fdfs->img, 0, 0) < 0)
		error_and_exit("initialise_mlx", "mlx_image_to_window");
	reset_fdfs(fdfs);
	render_map(fdfs);

	mlx_texture_t* icon = mlx_load_png("./docs/icon.png");
	mlx_set_icon(fdfs->mlx, icon);

	mlx_get_monitor_size(0, &width, &height);
	mlx_set_window_pos(fdfs->mlx, (width - WIN_W)/2, (height - WIN_H)/2);
}

void mlx_resize(int32_t width, int32_t height, void* param)
{
	t_fdfs	*fdfs = (t_fdfs *)param;

	if (!mlx_resize_image(fdfs->img, width, height))
		printf("ERROR AT IMAGE RESIZED");
	render_map(fdfs);
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
	mlx_loop_hook(fdfs->mlx, move, fdfs);
	mlx_loop_hook(fdfs->mlx, rotation, fdfs);
	mlx_key_hook(fdfs->mlx, key_hook, fdfs);
	mlx_mouse_hook(fdfs->mlx, mouse_hook, fdfs);
	mlx_scroll_hook(fdfs->mlx, mouse_scroll, fdfs);
	mlx_resize_hook(fdfs->mlx, mlx_resize, fdfs);
	mlx_loop(fdfs->mlx);
	mlx_terminate(fdfs->mlx);
	//free_all(fdfs);
	return (0);
}
