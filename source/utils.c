/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/08/09 13:26:07 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	error_and_exit(const char *func, const char *msg)
{
	printf("Error in function \"%s\": %s", func, msg);
	exit(-1);
}

void	free_all(t_fdfs *fdfs)
{
	mlx_delete_image(fdfs->mlx, fdfs->img);
	mlx_delete_image(fdfs->mlx, fdfs->menu);
	free_map(fdfs->map);
	if (fdfs->img)
		free(fdfs->img);
	if (fdfs->menu)
		free(fdfs->menu);
	free(fdfs);
}

void	isometric(t_fdfs *fdfs, int *x, int *y, int z)
{
	int	tmp_x;
	int	tmp_y;

	if (!fdfs->state.zenith)
		return ;
	tmp_x = *x;
	tmp_y = *y;
	*x = (tmp_x - tmp_y) * cos(DEGREE_30);
	*y = -z + (tmp_x + tmp_y) * sin(DEGREE_30);
}

t_point	new_point(int x, int y, t_fdfs *fdfs)
{
	t_point	new;

	new.x = x;
	new.y = y;
	new.z = fdfs->map->z_gen[y][x];
	if (fdfs->map->has_color)
		new.color = fdfs->map->color_file[y][x];
	else
		new.color = gen_gradient(fdfs, new.z);
	return (new);
}

void	mode_strange(t_fdfs *fdfs, int *x, int *y, int z)
{
	// Coordenadas esféricas
	double theta = (*x / (double)(fdfs->map->width - 1)) * M_PI;
	double phi = (*y / (double)(fdfs->map->height - 1)) * 2 * M_PI;
	// Altura y radio
	double r = fdfs->zoom + z; // R es el radio base

	// Coordenadas en la esfera
	*x = (int)(r * sin(theta) * cos(phi));
	*y = (int)(r * sin(theta) * sin(phi));
	*x += WIN_W / 2;
	*y += WIN_H / 2;

}

void	mode_strange00(t_fdfs *fdfs, int *x, int *y, int *z)
{
	float r = 10.0;
	float x_norm = 2 * *x  / (fdfs->map->width - 1) - 1;
    float y_norm = 2 * *y / (fdfs->map->height - 1) - 1;
    float theta = x_norm * M_PI;
    float phi = y_norm * (M_PI / 2);

	*x = r * cos(phi) * cos(theta);
	*y = r * cos(phi) * sin(theta);
	*z = r * sin(phi);

}

void	sphere(t_fdfs *fdfs, int *x, int *y, int *z)
{
	/*
	double r = sqrt((pow((double)x, 2)) + pow((double)y, 2) + pow((double)z, 2));
	float x_norm = 2 * *x  / (fdfs->map->width - 1) - 1;
    float y_norm = 2 * *y / (fdfs->map->height - 1) - 1;
    float theta = x_norm * M_PI;
    float phi = y_norm * (M_PI / 2);
	*x = r * cos(phi) * cos(theta);
	*y = r * cos(phi) * sin(theta);
	*/
	double theta = (*x / (double)(fdfs->map->width - 1)) * M_PI;
	double phi = (*y / (double)(fdfs->map->height - 1)) * 2 * M_PI;
	//	(void)fdfs;
	//double theta = atan(*y / *x);
	//double phi = atan(*z / sqrt((*x^2) + (*y^2)));
	double r = RADIX + sqrt((*x^2) + (*y^2) + (*z^2));
	//double r = sqrt ((*x^2) + (*y^2) + (*z^2));
	//x_norm = r * cos (theta);
	//*y = r * sin (theta);
	*x = (int)(r * cos (phi) * cos (theta));
	*y = (int)(r * cos (phi) * sin (theta));
	//*z = (int)(r * sin (phi));
	*x += WIN_W / 2;
	*y += WIN_H / 2;
}

void	cilindro(t_fdfs *fdfs, int *x, int *y, int *z)
{
	(void)z;
	double theta = (*x / (double)(fdfs->map->width - 1)) * M_PI;
	double phi = (*y / (double)(fdfs->map->height - 1)) * 2 * M_PI;
	double r = RADIX; // + sqrt((*x^2) + (*y^2));

	*x = (int)(r * cos (theta));
	*y = (int)(r * sin (phi));
	*z = (int)(r * sin (phi));
	*x += WIN_W / 2;
	*y += WIN_H / 2;
}

void	mode_strange01(t_fdfs *fdfs, int *x, int *y, int *z)
{
	(void)z;
	double theta = (*x / (double)(fdfs->map->width - 1)) * M_PI;
	double phi = (*y / (double)(fdfs->map->height - 1)) * 2 * M_PI;
	double r = RADIX; // + sqrt((*x^2) + (*y^2));

	*x = (int)(r * cos (theta));
	*y = (int)(r * sin (phi));
	*z = (int)(r * sin (phi));
	*x += WIN_W / 2;
	*y += WIN_H / 2;
}

t_point	set_changes(t_fdfs *fdfs, t_point point)
{
	if (fdfs->state.mod_04)
		mode_strange00(fdfs, &point.x, &point.y, &point.z);

	point.x *= fdfs->zoom;
	point.y *= fdfs->zoom;
	point.z *= (fdfs->zoom / 10) * fdfs->flat;
	rotate_x(fdfs, &point.y, &point.z);
	rotate_y(fdfs, &point.x, &point.z);
	rotate_z(fdfs, &point.x, &point.y);
	if (!fdfs->state.mod_03)
		isometric(fdfs, &point.x, &point.y, point.z);
	point.x += fdfs->step_x;
	point.y += fdfs->step_y;
	if (fdfs->state.mod_00)
		sphere(fdfs, &point.x, &point.y, &point.z);
	if (fdfs->state.mod_01)
		cilindro(fdfs, &point.x, &point.y, &point.z);
	if (fdfs->state.mod_02)
		mode_strange(fdfs, &point.x, &point.y, point.z);
	if (fdfs->state.mod_03)
		mode_strange01(fdfs, &point.x, &point.y, &point.z);
	return (point);
}

void	reset_fdfs(t_fdfs *fdfs)
{
	fdfs->zoom = ft_maximum((WIN_W / fdfs->map->width / 2), (WIN_H / fdfs->map->height / 2));
	fdfs->step_x = WIN_W / 2;
	fdfs->step_y = (WIN_H - fdfs->map->height * fdfs->zoom) / 2;
	fdfs->flat = 1 + (fdfs->zoom / fdfs->map->max_z);
	fdfs->rotate_x = 0;
	fdfs->rotate_y = 0;
	fdfs->rotate_z = 0;
	fdfs->state.menu = 0;
	fdfs->menu->enabled = false;
	fdfs->state.zenith = 1;
	fdfs->state.bg_color = 0x000000FF;
	fdfs->state.dark_zero = 0;
	fdfs->state.disable_clean = 0;
	fdfs->state.extra_pixel = 0;
	fdfs->state.mirror = 0;
	fdfs->state.desplace = 0;

	fdfs->state.one_color = 0;
	fdfs->state.rnd_color = 0;
	fdfs->state.map_color = 0;
	fdfs->state.multi_color = 0;
	fdfs->state.live = 0;
	fdfs->state.clon = 0;

	fdfs->state.mod_00 = 0;
	fdfs->state.mod_01 = 0;
	fdfs->state.mod_02 = 0;
	fdfs->state.mod_03 = 0;
	fdfs->state.mod_04 = 0;
	set_palette(&fdfs->state.palette, 1);
}
