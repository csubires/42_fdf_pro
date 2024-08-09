/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/08/09 13:54:57 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	render_menu(t_fdfs *fdfs)
{
	int		y;
	int		x;

	if (!(fdfs->menu = mlx_new_image(fdfs->mlx, MENU_W, MENU_H)))
		error_and_exit("initialise_mlx", "mlx_image_t");

	set_bgcolor(fdfs->menu, MENU_BG);

	x = 0;
	while (x++ < MENU_W - 1)
	{
		y = 0;
		while (y++ < MENU_H - 1)
		{
			if (x < 5 || x > (MENU_W - 6) || y < 5 || y > (MENU_H - 6) || \
			y == 170 || y == 310 || y == 490 || y == 630)
				mlx_put_pixel(fdfs->menu, x, y, MENU_BR);
		}
	}

	x = (fdfs->img->width - MENU_W) / 2;
	y = (fdfs->img->height - MENU_H) / 2;
	mlx_put_string(fdfs->mlx, M_TEXT_00, x + 40, y += 50);
	mlx_put_string(fdfs->mlx, M_TEXT_02, x + 40, y += 40);
	mlx_put_string(fdfs->mlx, M_TEXT_03, x + 40, y += 40);
	mlx_put_string(fdfs->mlx, M_TEXT_04, x + 40, y += 60);
	mlx_put_string(fdfs->mlx, M_TEXT_05, x + 130, y += 40);
	mlx_put_string(fdfs->mlx, M_TEXT_06, x + 40, y += 40);
	mlx_put_string(fdfs->mlx, M_TEXT_07, x + 40, y += 60);
	mlx_put_string(fdfs->mlx, M_TEXT_08, x + 120, y += 40);
	mlx_put_string(fdfs->mlx, M_TEXT_09, x + 40, y += 40);
	mlx_put_string(fdfs->mlx, M_TEXT_10, x + 220, y += 40);
	mlx_put_string(fdfs->mlx, M_TEXT_11, x + 40, y += 60);
	mlx_put_string(fdfs->mlx, M_TEXT_12, x + 70, y += 40);
	mlx_put_string(fdfs->mlx, M_TEXT_13, x + 70, y += 40);
	mlx_put_string(fdfs->mlx, M_TEXT_14, x + 40, y += 70);
	mlx_put_string(fdfs->mlx, M_TEXT_15, x + 40, y += 40);
	x = (fdfs->img->width - MENU_W) / 2;
	y = (fdfs->img->height - MENU_H) / 2;
	mlx_put_string(fdfs->mlx, M_TEXT_16, x + 600, y += 40);
	mlx_put_string(fdfs->mlx, M_TEXT_17, x + 600, y += 40);
	mlx_put_string(fdfs->mlx, M_TEXT_18, x + 600, y += 40);
	mlx_put_string(fdfs->mlx, M_TEXT_19, x + 600, y += 70);
	mlx_put_string(fdfs->mlx, M_TEXT_20, x + 600, y += 40);
	mlx_put_string(fdfs->mlx, M_TEXT_21, x + 600, y += 40);
	mlx_put_string(fdfs->mlx, M_TEXT_22, x + 600, y += 70);

	if (mlx_image_to_window(fdfs->mlx, fdfs->menu, (fdfs->img->width - MENU_W)/2, (fdfs->img->height - MENU_H)/2) < 0)
			error_and_exit("initialise_mlx", "mlx_image_to_window");

}
