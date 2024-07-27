/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/07/27 15:30:06 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	render_menu(mlx_image_t *menu)
{

	int		x;
	int		y;
	int32_t	width = menu->width;
	int32_t	height = menu->height;


	set_bgcolor(menu, MENU_BG);

	x = -1;
	while (x++ < width)
	{
		y = -1;
		while (y++ < height)
		{
			if (x < 5 || x > (width - 6) || y < 5 || y > (height - 6) || \
			y == 160 || y == 280 || y == 420 || y == 530)
				mlx_put_pixel(menu, x, y, MENU_BR);
		}
	}
	return (1);
}

void	show_menu(t_fdfs *fdfs)
{
	int		y;
	int		x;

	x = (WIN_W - fdfs->menu->width) / 2;
	y = (WIN_H - fdfs->menu->height) / 2;
	if (mlx_image_to_window(fdfs->mlx, fdfs->menu, x, y) < 0)
        error_and_exit("initialise_mlx", "mlx_image_to_window");
	mlx_put_string(fdfs->mlx, M_TEXT_00, x + 40, y += 40);
	mlx_put_string(fdfs->mlx, M_TEXT_02, x + 40, y += 40);
	mlx_put_string(fdfs->mlx, M_TEXT_03, x + 40, y += 40);
	mlx_put_string(fdfs->mlx, M_TEXT_04, x + 40, y += 60);
	mlx_put_string(fdfs->mlx, M_TEXT_05, x + 130, y += 40);
	mlx_put_string(fdfs->mlx, M_TEXT_06, x + 40, y += 40);
	mlx_put_string(fdfs->mlx, M_TEXT_07, x + 40, y += 50);
	mlx_put_string(fdfs->mlx, M_TEXT_08, x + 120, y += 40);
	mlx_put_string(fdfs->mlx, M_TEXT_09, x + 40, y += 40);
	mlx_put_string(fdfs->mlx, M_TEXT_10, x + 220, y += 40);
	mlx_put_string(fdfs->mlx, M_TEXT_11, x + 40, y += 60);
	mlx_put_string(fdfs->mlx, M_TEXT_12, x + 70, y += 40);
	mlx_put_string(fdfs->mlx, M_TEXT_13, x + 70, y += 40);
	mlx_put_string(fdfs->mlx, M_TEXT_14, x + 40, y += 60);
	mlx_put_string(fdfs->mlx, M_TEXT_15, x + 40, y += 40);
}

static void	init_bresenham(t_point *start, t_point *end,
t_point *diff, t_point *sign)
{
	sign->x = -1;
	sign->y = -1;
	if (start->x < end->x)
		sign->x = 1;
	if (start->y < end->y)
		sign->y = 1;
	diff->x = ft_abs(end->x - start->x);
	diff->y = ft_abs(end->y - start->y);
}

static void	bresenham(t_fdfs *fdfs, t_point start, t_point end)
{
	t_point	cur;
	t_point	sign;
	t_point	diff;
	int		line;
	int		tmp;

	init_bresenham(&start, &end, &diff, &sign);
	line = diff.x - diff.y;
	cur = start;
		int color = random_color();
	while (cur.x != end.x || cur.y != end.y)
	{

 		if (cur.x >= fdfs->img->width || cur.y >= fdfs->img->height)
			break;

		mlx_put_pixel(fdfs->img, cur.x, cur.y, get_color(start, end, cur, diff));

		// MODE MULTICOLOR
		if (fdfs->state.multi_color)
		{
			int x = 0;
			while (x++ < 5)
			{
				mlx_put_pixel(fdfs->img, cur.x+x, cur.y+x, color);
				mlx_put_pixel(fdfs->img, cur.x-x, cur.y-x, color);
				mlx_put_pixel(fdfs->img, cur.x+x, cur.y-x, color);
				mlx_put_pixel(fdfs->img, cur.x-x, cur.y+x, color);
			}
		}

		// MODO EXTRA PIXEL
		if (fdfs->state.extra_pixel)
		{
			int x = 0;
			while (x++ < 5)
			{
				mlx_put_pixel(fdfs->img, cur.x+x, cur.y+x, get_color(start, end, cur, diff));
				mlx_put_pixel(fdfs->img, cur.x-x, cur.y-x, get_color(start, end, cur, diff));
				mlx_put_pixel(fdfs->img, cur.x+x, cur.y-x, get_color(start, end, cur, diff));
				mlx_put_pixel(fdfs->img, cur.x-x, cur.y+x, get_color(start, end, cur, diff));
			}
		}


		tmp = line * 2;
		if (tmp > -diff.y)
		{
			line -= diff.y;
			cur.x += sign.x;
		}
		if (tmp < diff.x)
		{
			line += diff.x;
			cur.y += sign.y;
		}
	}
}

void	render_map(void *param)
{
	t_fdfs *fdfs = (t_fdfs *)param;

	int	x;
	int	y;

	if (!fdfs->state.disable_clean && !fdfs->state.bg_color)
		set_bgcolor(fdfs->img, 0x000000FF);

	if (fdfs->zoom)
	{
		y = -1;
		while (++y < fdfs->map->height)
		{
			x = -1;
			while (++x < fdfs->map->width)
			{
				if (x < fdfs->map->width - 1)
					bresenham(fdfs,
						get_coordinate(fdfs, new_point(x, y, fdfs)),
						get_coordinate(fdfs, new_point(x + 1, y, fdfs)));
				if (y < fdfs->map->height - 1)
					bresenham(fdfs,
						get_coordinate(fdfs, new_point(x, y, fdfs)),
						get_coordinate(fdfs, new_point(x, y + 1, fdfs)));
			}
		}

		if (fdfs->state.mirror)
		{
			fdfs->flat = fdfs->flat * -1;
			y = -1;
			while (++y < fdfs->map->height)
			{
				x = -1;
				while (++x < fdfs->map->width)
				{
					if (fdfs->map->z_gen[y][x] < 5)
						continue ;

					if (x < fdfs->map->width - 1)
						bresenham(fdfs,
							get_coordinate(fdfs, new_point(x, y, fdfs)),
							get_coordinate(fdfs, new_point(x + 1, y, fdfs)));
					if (y < fdfs->map->height - 1)
						bresenham(fdfs,
							get_coordinate(fdfs, new_point(x, y, fdfs)),
							get_coordinate(fdfs, new_point(x, y + 1, fdfs)));
				}
			}
		}
	}


}
