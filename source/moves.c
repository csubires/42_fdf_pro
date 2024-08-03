/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 08:56:20 by csubires          #+#    #+#             */
/*   Updated: 2024/08/02 20:24:40 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	rotate_x(t_fdfs *fdfs, int *y, int *z)
{
	float	tmp_y;

	tmp_y = *y;
	*y = (tmp_y * cos(fdfs->rotate_x)) + (*z * sin(fdfs->rotate_x));
	*z = (-tmp_y * sin(fdfs->rotate_x)) + (*z * cos(fdfs->rotate_x));
}

void	rotate_y(t_fdfs *fdfs, int *x, int *z)
{
	float	tmp_x;

	tmp_x = *x;
	*x = (*x * cos(fdfs->rotate_y)) + (*z * sin(fdfs->rotate_y));
	*z = (-tmp_x * sin(fdfs->rotate_y)) + (*z * cos(fdfs->rotate_y));
}

void	rotate_z(t_fdfs *fdfs, int *x, int *y)
{
	float	tmp_x;

	tmp_x = *x;
	*x = (*x * cos(fdfs->rotate_z)) - (*y * sin(fdfs->rotate_z));
	*y = (tmp_x * sin(fdfs->rotate_z)) + (*y * cos(fdfs->rotate_z));
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
