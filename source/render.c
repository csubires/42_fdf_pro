/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/08/26 15:50:57 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	is_into_screen(mlx_image_t *img, int x, int y)
{
	return (x > 0 && y > 0
		&& x < (int)img->width
		&& y < (int)img->height
	);
}

static void	init_bresenham(t_point *start, t_point *end, t_point *diff, t_point *sign)
{
	sign->x = (start->x < end->x) ? 1 : -1;
	sign->y = (start->y < end->y) ? 1 : -1;
	diff->x = abs(end->x - start->x);
	diff->y = abs(end->y - start->y);
}

static void	bresenham(t_fdfs *fdfs, t_point start, t_point end)
{
	t_point	cur;
	t_point	sign;
	t_point	diff;
	int		line;
	int		tmp1;
	int		color = random_color();

	init_bresenham(&start, &end, &diff, &sign);
	line = diff.x - diff.y;
	cur = start;
	while ((cur.x != end.x || cur.y != end.y) && is_into_screen(fdfs->img, cur.x, cur.y))
	{
		if (fdfs->state.one_color)
		{
			if (fdfs->state.dark_zero && (end.z - start.z < 5))
				mlx_put_pixel(fdfs->img, cur.x, cur.y, 0xFFFF00FF);
			else
				mlx_put_pixel(fdfs->img, cur.x, cur.y, fdfs->state.one_color);
		}
		else
			mlx_put_pixel(fdfs->img, cur.x, cur.y, get_color(start, end, cur, diff));

		// MODE MULTICOLOR
		if (fdfs->state.multi_color)
		{
			tmp1 = 0;
			while (tmp1++ < LINE_SIZE)
			{
				if (is_into_screen(fdfs->img, cur.x+tmp1, cur.y+tmp1))
					mlx_put_pixel(fdfs->img, cur.x+tmp1, cur.y+tmp1, color);
				if (is_into_screen(fdfs->img, cur.x-tmp1, cur.y-tmp1))
					mlx_put_pixel(fdfs->img, cur.x-tmp1, cur.y-tmp1, color);
				if (is_into_screen(fdfs->img, cur.x+tmp1, cur.y-tmp1))
					mlx_put_pixel(fdfs->img, cur.x+tmp1, cur.y-tmp1, color);
				if (is_into_screen(fdfs->img, cur.x-tmp1, cur.y+tmp1))
					mlx_put_pixel(fdfs->img, cur.x-tmp1, cur.y+tmp1, color);
			}
		}

		// MODO EXTRA PIXEL
		if (fdfs->state.extra_pixel)
		{
			tmp1 = 0;
			while (tmp1++ < LINE_SIZE)
			{
				if (is_into_screen(fdfs->img, cur.x+tmp1, cur.y+tmp1))
					mlx_put_pixel(fdfs->img, cur.x+tmp1, cur.y+tmp1, get_color(start, end, cur, diff));
				if (is_into_screen(fdfs->img, cur.x-tmp1, cur.y-tmp1))
					mlx_put_pixel(fdfs->img, cur.x-tmp1, cur.y-tmp1, get_color(start, end, cur, diff));
				if (is_into_screen(fdfs->img, cur.x+tmp1, cur.y-tmp1))
					mlx_put_pixel(fdfs->img, cur.x+tmp1, cur.y-tmp1, get_color(start, end, cur, diff));
				if (is_into_screen(fdfs->img, cur.x-tmp1, cur.y+tmp1))
					mlx_put_pixel(fdfs->img, cur.x-tmp1, cur.y+tmp1, get_color(start, end, cur, diff));
			}
		}

		tmp1 = line * 2;
		if (tmp1 > -diff.y)
		{
			line -= diff.y;
			cur.x += sign.x;
		}
		if (tmp1 < diff.x)
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

	t_point	p1;
	t_point	p2;
	clock_t	t = clock();

	if (!fdfs->state.disable_clean && fdfs->state.bg_color)
		set_bgcolor(fdfs->img, fdfs->state.bg_color);

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

				if (fdfs->state.mod_01 == 1 && !es_visible(x, y, fdfs->map->z_gen[y][x]))
					continue ;

				p1 = set_changes(fdfs, new_point(x, y, fdfs));
				if (x < fdfs->map->width - 1)
					p2 = set_changes(fdfs, new_point(x + 1, y, fdfs));
				if (!fdfs->state.desplace)
					bresenham(fdfs, p1, p2);
				if (y < fdfs->map->height - 1)
					p2 = set_changes(fdfs, new_point(x, y + 1, fdfs));
				if (!fdfs->state.desplace)
					bresenham(fdfs, p1, p2);
			}
		}

		// MODO ESPEJO
		if (fdfs->state.mirror)
		{
			fdfs->flat = -fdfs->flat;
			y = -1;
			while (++y < fdfs->map->height)
			{
				x = -1;
				while (++x < fdfs->map->width)
				{
					if (fdfs->map->z_gen[y][x] < 5)
						continue ;
					p1 = set_changes(fdfs, new_point(x, y, fdfs));
					if (x < fdfs->map->width - 1)
						p2 = set_changes(fdfs, new_point(x + 1, y, fdfs));
					if (!fdfs->state.desplace)
						bresenham(fdfs, p1, p2);
					if (y < fdfs->map->height - 1)
						p2 = set_changes(fdfs, new_point(x, y + 1, fdfs));
					if (!fdfs->state.desplace)
						bresenham(fdfs, p1, p2);
				}
			}
		}
	}

	t = clock() - t;
	//printf("Performance: %f, ", ((double)t) / CLOCKS_PER_SEC);

}
