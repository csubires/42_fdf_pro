/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:39:36 by csubires          #+#    #+#             */
/*   Updated: 2024/07/16 12:58:47 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../lib/MLX42/include/MLX42/MLX42.h"

#ifndef STRUCTS_H
# define STRUCTS_H
// MAP FILE
typedef struct s_map
{
	int	width;
	int	height;
	int	has_color;
	int	**color_file;
	int	**z_gen;
	int	min_z;
	int	max_z;
}	t_map;

// SET COLORS
typedef struct s_palette
{
	int32_t		color_1;
	int32_t		color_2;
	int32_t		color_3;
	int32_t		color_4;
	int32_t		color_5;
	int32_t		color_6;
	int32_t		color_7;
	int32_t		color_8;
}	t_palette;

// OPTIONS OF PROGRAM
typedef struct s_state
{
	int			zenith;
	int			menu;
	int			disable_clean;
	int			bg_color;
	int			extra_pixel;
	int			dark_zero;
	int			desplace;

	int			live;
	int			clon;

	int			mirror;
	int			mod_00;
	int			mod_01;
	int			mod_02;
	int			mod_03;
	int			mod_04;

	int			one_color;
	int			rnd_color;
	int			map_color;
	int			multi_color;

	t_palette	palette;
}	t_state;

// POINT
typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

// VARS FOR A INSTANCE OF PROGRAM
typedef struct s_fdfs
{
	void		*mlx;
	t_map		*map;
	mlx_image_t	*img;
	mlx_image_t	*menu;
	int32_t		step_x;
	int32_t		step_y;
	float		rotate_x;
	float		rotate_y;
	float		rotate_z;
	t_state		state;
	float		zoom;
	float		flat;
}	t_fdfs;

#endif
