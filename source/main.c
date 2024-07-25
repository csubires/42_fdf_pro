/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/07/25 20:10:12 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	close_win(t_fdfs *fdfs)
{
	free_all(fdfs);
	exit (0);
	return (0);
}

static int	initialise_fdfs(t_fdfs *fdfs, t_map *map)
{
	fdfs->map = map;
	fdfs->img = (mlx_image_t *)ft_calloc(1, sizeof(mlx_image_t));
	if (!fdfs->img)
		return (1);
	fdfs->menu = (mlx_image_t *)ft_calloc(1, sizeof(mlx_image_t));
	if (!fdfs->menu)
		return (1);
	reset_fdfs(fdfs);
	return (0);
}

static void	initialise_mlx(t_fdfs *fdfs)
{
	// mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_t* mlx = mlx_init(WIN_W, WIN_H, "FDF PRO - CSUBIRES", true);
	if (!mlx)
		error_and_exit("initialise_mlx", "mlx_init");
	mlx_image_t* img = mlx_new_image(mlx, WIN_W, WIN_H);
	if (!img)
		error_and_exit("initialise_mlx", "mlx_image_t");
	fdfs->mlx = mlx;
	fdfs->img = img;
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
        error_and_exit("initialise_mlx", "mlx_image_to_window");
}

int	main(int argc, char *argv[])
{
	t_map	*map;
	t_fdfs	*fdfs;

	map = 0;
	srand(time(0));
	parse_args(&map, argc, argv);
	fdfs = (t_fdfs *)ft_calloc(1, sizeof(t_fdfs));
	if (!fdfs || initialise_fdfs(fdfs, map))
	{
		free_all(fdfs);
		error_and_exit("initialise_mlx", "initialise_fdfs or ft_calloc");
	}
	initialise_mlx(fdfs);
	render_menu(fdfs, 400, 600);
	mlx_loop_hook(fdfs->mlx, &move, fdfs);
	mlx_loop_hook(fdfs->mlx, &rotation, fdfs);
	mlx_scroll_hook(fdfs->mlx, &my_scrollhook, NULL);
	mlx_loop(fdfs->mlx);
	mlx_delete_image(fdfs->mlx, fdfs->img);
	mlx_terminate(fdfs->mlx);
	free_all(fdfs);
	return (0);
}
