/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/08/26 16:20:54 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static double	interpolate(int start, int end, int current)
{
	int	len_line = end - start;
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

	if (fdfs->state.dark_zero && (cur_z < 1 && cur_z > 0 ))
		return (0xFF00F0FF);

	if (fdfs->state.dark_zero && cur_z == 0)
		return (fdfs->state.bg_color);

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

int psychedelic_color(int x, int y) {
    double r = 0.5 + 0.5 * sin(0.1 * x + 0.1 * y);
    double g = 0.5 + 0.5 * sin(0.1 * x + 0.2 * y);
    double b = 0.5 + 0.5 * sin(0.1 * x + 0.3 * y);

    int red = (int)(r * 255);
    int green = (int)(g * 255);
    int blue = (int)(b * 255);

    return get_rgba(red, green, blue, 255);
}


void draw_kaleidoscope(mlx_image_t *img)
{
    int cx = WIN_W / 2;
    int cy = WIN_H / 2;
    double angle_step = 2 * M_PI / rand() + 20;  // Ángulo para cada segmento

    for (int y = -cy; y < cy; y++) {
        for (int x = -cx; x < cx; x++) {
            // Calculamos el ángulo y la distancia desde el centro
            double angle = atan2(y, x);
            double distance = sqrt(x * x + y * y);

            // Normalizar el ángulo al primer segmento (0 a angle_step)
            if (angle < 0) {
                angle += 2 * M_PI;
            }
            angle = fmod(angle, angle_step);

            // Determinar la nueva posición x' y' usando el ángulo normalizado y la distancia
            int x_prime = (int)(distance * cos(angle));
            int y_prime = (int)(distance * sin(angle));

            // Ajustar las coordenadas al centro de la imagen
            int draw_x = cx + x_prime;
            int draw_y = cy + y_prime;

            // Generar un color psicodélico basado en las coordenadas
            int color = psychedelic_color(draw_x, draw_y);

            // Dibujar el pixel en la imagen
			if (is_into_screen(img, draw_x, draw_y))
            	mlx_put_pixel(img, draw_x, draw_y, color);
        }
    }
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

static void	set_palette_one(t_palette *palette, int color)
{
	palette->color_1 = color;
	palette->color_2 = color;
	palette->color_3 = color;
	palette->color_4 = color;
	palette->color_5 = color;
	palette->color_6 = color;
	palette->color_7 = color;
	palette->color_8 = color;
}

static void	set_palette_zero(t_palette *palette, int color)
{
	palette->color_1 = color;
	palette->color_2 = color;
	palette->color_3 = color;
	palette->color_4 = color;
	palette->color_5 = color;
	palette->color_6 = color;
	palette->color_7 = color;
	palette->color_8 = color;
}


void	set_palette(t_palette *palette, int pal)
{
	switch (pal)
	{
	case (0):
		set_palette_rdm(palette);
		break;
	case (1):
		set_palete_default(palette);
		break;
	case (2):
		set_palette_map(palette);
		break;
	case (3):
		set_palette_one(palette, random_color());
		break;
	case (4):
		set_palette_zero(palette, 0xFF0000FF);
		break;
	default:
		break;
	}
}
