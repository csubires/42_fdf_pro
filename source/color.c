/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/07/30 12:51:08 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static double	interpolate(int start, int end, int current)
{
	int	len_line;

	len_line = end - start;
	if (!len_line)
		return (1.0);
	return ((double)(current - start) / len_line);
}

int	get_color(t_point start, t_point end, t_point current, t_point diff)
{
	int		r;
	int		g;
	int		b;
	double	t;

	if (current.color == end.color)
		return (current.color);
	if (diff.x > diff.y)
		t = interpolate(start.x, end.x, current.x);
	else
		t = interpolate(start.y, end.y, current.y);

	r = (int)(((1 - t) * get_r(start.color) + t * get_r(end.color)));
	g = (int)(((1 - t) * get_g(start.color) + t * get_g(end.color)));
	b = (int)(((1 - t) * get_b(start.color) + t * get_b(end.color)));
	return (get_rgba(r, g, b, 0xFF));
}

int	gen_gradient(t_fdfs *fdfs, int cur_z)
{
	double	gradient = interpolate(fdfs->map->min_z, fdfs->map->max_z, cur_z);

	if (!fdfs->state.rnd_color && !fdfs->state.map_color)
		set_palette(&fdfs->state.palette, 1);

	if (gradient < 0.15)
		return (fdfs->state.palette.color_1);
	else if (gradient < 0.35)
		return (fdfs->state.palette.color_2);
	else if (gradient < 0.5)
		return (fdfs->state.palette.color_3);
	else if (gradient < 0.54)
		return (fdfs->state.palette.color_4);
	else if (gradient < 0.57)
		return (fdfs->state.palette.color_5);
	else if (gradient < 0.6)
		return (fdfs->state.palette.color_6);
	else if (gradient < 0.8)
		return (fdfs->state.palette.color_7);
	else
		return (fdfs->state.palette.color_8);
}

void	set_bgcolor(mlx_image_t *img, int color)
{
	uint32_t y = -1;
	uint32_t x = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
			mlx_put_pixel(img, x, y, color);
	}
}

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int get_r(int rgba)
{
	return ((rgba >> 24) & 0xFF);
}

int get_g(int rgba)
{
	return ((rgba >> 16) & 0xFF);
}

int get_b(int rgba)
{
	return ((rgba >> 8) & 0xFF);
}

int get_a(int rgba)
{
	return (rgba & 0xFF);
}

int	random_color(void)
{
	return (get_rgba(rand() % 0xFF, rand() % 0xFF, rand() % 0xFF, rand() % 0xFF));
}

static void	set_palete_default(t_palette *palette)
{
	palette->color_1 = COLOR_DF_1;
	palette->color_2 = COLOR_DF_2;
	palette->color_3 = COLOR_DF_3;
	palette->color_4 = COLOR_DF_4;
	palette->color_5 = COLOR_DF_5;
	palette->color_6 = COLOR_DF_6;
	palette->color_7 = COLOR_DF_7;
	palette->color_8 = COLOR_DF_8;
}

static void	set_palette_map(t_palette *palette)
{
	palette->color_1 = COLOR_MP_1;
	palette->color_2 = COLOR_MP_2;
	palette->color_3 = COLOR_MP_3;
	palette->color_4 = COLOR_MP_4;
	palette->color_5 = COLOR_MP_5;
	palette->color_6 = COLOR_MP_6;
	palette->color_7 = COLOR_MP_7;
	palette->color_8 = COLOR_MP_8;
}

static void	set_palette_rdm(t_palette *palette)
{
	palette->color_1 = random_color();
	palette->color_2 = random_color();
	palette->color_3 = random_color();
	palette->color_4 = random_color();
	palette->color_5 = random_color();
	palette->color_6 = random_color();
	palette->color_7 = random_color();
	palette->color_8 = random_color();
}

void	set_palette(t_palette *palette, int selected)
{
	if (selected == 0)
		set_palette_rdm(palette);
	if (selected == 1)
		set_palete_default(palette);
	if (selected == 2)
		set_palette_map(palette);
}
