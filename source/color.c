/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/07/27 15:15:18 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static double	interpolate(int32_t start, int32_t end, int32_t current)
{
	int32_t	len_line;

	len_line = end - start;
	if (!len_line)
		return (1.0);
	return ((double)(current - start) / len_line);
}

int	get_color(t_point start, t_point end, t_point current, t_point diff)
{
	int32_t		color;
	int32_t		c1;
	int32_t		c2;
	double	t;

	if (current.color == end.color)
		return (current.color);
	if (diff.x > diff.y)
		t = interpolate(start.x, end.x, current.x);
	else
		t = interpolate(start.y, end.y, current.y);
	color = 0;
	c1 = (start.color >> 16) & 0xFF;
	c2 = (end.color >> 16) & 0xFF;
	color |= (int32_t)(((1 - t) * c1 + t * c2)) << 16;
	c1 = (start.color >> 8) & 0xFF;
	c2 = (end.color >> 8) & 0xFF;
	color |= ((int32_t)((1 - t) * c1 + t * c2)) << 8;
	c1 = start.color & 0xFF;
	c2 = end.color & 0xFF;
	color |= (int32_t)((1 - t) * c1 + t * c2);
	return (color);
}

int	generate_color(t_fdfs *fdfs, int cur_z)
{
	double	gradient;

	if (!fdfs->state.rnd_color && !fdfs->state.map_color)
		set_palette(&fdfs->state.palette, 1);
	gradient = interpolate(fdfs->map->min_z, fdfs->map->max_z, cur_z);

	if (fdfs->state.dark_zero && gradient < 0.15)
		return (0x00000000);

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
	int32_t y = -1;
	int32_t x = -1;
	while (++y < WIN_H)
	{
		x = -1;
		while (++x < WIN_W)
			mlx_put_pixel(img, x, y, color);
	}
}
