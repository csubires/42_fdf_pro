/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/07/19 13:11:23 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <string.h>
# include <math.h>
# include <stdlib.h>
# include <time.h>
# include <stdio.h>
# include "colors.h"
# include "config.h"
# include "keys.h"
# include "structs.h"
# include "../libft/libft.h"
# include "../mlx42/include/MLX42/MLX42.h"

# include <stdint.h>
# include <memory.h>

# define BPP sizeof(int32_t)


void	zoom_and_altitude(int keycode, t_fdfs *fdfs);
void	move(void *param);
void	rotation(void *param);
void	state(int keycode, t_fdfs *fdfs);

// COLOR.C
int		get_color(t_point start, t_point end, t_point current, t_point delta);
int		generate_color(t_fdfs *fdfs, int cur_z);
void	change_bgcolor(t_fdfs *fdfs, int color);

// COLOR_UTILS.C

int get_rgba(int r, int g, int b, int a);
int get_r(int rgba);
int get_g(int rgba);
int get_b(int rgba);
int get_a(int rgba);


int		random_color(void);
void	set_palette(t_palette *palette, int selected);

// KEYS.C
int		key_event(int keycode, t_fdfs *fdfs);
int		mouse_hook(int button, int x, int y, void *p);

// MAIN.C
int		close_win(t_fdfs *fdfs);

// MAP.C
void	free_map(t_map *map);
void	set_z_limits(t_map *map);
void	create_struct_mem(t_map *map);
t_map	*initialise_map(char *file);

// PARSE.C
void	parse_args(t_map **map, int argc, char *argv[]);

// RENDER.C
int		render_menu(t_fdfs *fdfs, int width, int height);
void	show_menu(t_fdfs *fdfs);
void	render_map(t_fdfs *fdfs);

// RENDER_UTILS.C
void	error_and_exit(const char *err, const char *msg);
void	rotate_x(t_fdfs *fdfs, int *y, int *z);
void	rotate_y(t_fdfs *fdfs, int *x, int *z);
void	rotate_z(t_fdfs *fdfs, int *x, int *y);


// UTILS.C
void	free_all(t_fdfs *fdfs);
void	isometric(t_fdfs *fdfs, int *x, int *y, int z);
t_point	new_point(int x, int y, t_fdfs *fdfs);
t_point	get_coordinate(t_fdfs *fdfs, t_point point);
void	reset_fdfs(t_fdfs *fdfs);

void	ft_hook(void *param);
void my_scrollhook(double xdelta, double ydelta, void* param);

#endif
