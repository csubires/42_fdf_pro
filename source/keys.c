/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/07/25 20:10:37 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void my_scrollhook(double xdelta, double ydelta, void* param)
{
	// Simple up or down detection.
	if (ydelta > 0)
		printf("Up!");
	else if (ydelta < 0)
		printf("Down!");

	// Can also detect a mousewheel that goes along the X (e.g: MX Master 3)
	if (xdelta < 0)
		printf("Sliiiide to the left!");
	else if (xdelta > 0)
		printf("Sliiiide to the right!");
}




void	zoom_and_altitude(int keycode, t_fdfs *fdfs)
{
	if (keycode == KEY_Q && fdfs->zoom > 0)
		fdfs->zoom -= ZOOM_STEP;
	if (keycode == KEY_E && fdfs->zoom < 100)
		fdfs->zoom += ZOOM_STEP;
	if (keycode == KEY_G)
		if (fdfs->flat < 50)
			fdfs->flat += ALTITUDE_STEP;
	if (keycode == KEY_V)
		if (fdfs->flat > -50)
			fdfs->flat -= ALTITUDE_STEP;
}


int mouse_hook(int button, int x, int y, void *p)
{
	ft_printf("Mouse button %d at %dx%d.\n", button, x, y);
	t_fdfs *fdfs = p;

	if (button == 1)
		fdfs->rotate_z += ROT_STEP;

	if (button == 2)
		fdfs->state.zenith = !fdfs->state.zenith;


	if (button == 3)
		fdfs->rotate_z -= ROT_STEP;

	if (button == 4)
	{


		int medx = WIN_W / 2;
		int medy = WIN_H / 2;


		if (x < medx && y < medy) // 1
		{
			fdfs->step_x += 5;
			fdfs->step_y += 5;
		}

		if (x > medx && y < medy) // 2
		{
			fdfs->step_x -= 5;
			fdfs->step_y += 5;
		}

		if (x < medx && y > medy) // 3
		{
			fdfs->step_x += 5;
			fdfs->step_y -= 5;
		}

		if (x > medx && y > medy) // 4
		{
			fdfs->step_x -= 5;
			fdfs->step_y -= 5;
		}

		fdfs->zoom += ZOOM_STEP;
	}

	if (button == 5)
	{

		int medx = WIN_W / 2;
		int medy = WIN_H / 2;


		if (x < medx && y < medy) // 1
		{
			fdfs->step_x -= 5;
			fdfs->step_y -= 5;
		}

		if (x > medx && y < medy) // 2
		{
			fdfs->step_x += 5;
			fdfs->step_y -= 5;
		}

		if (x < medx && y > medy) // 3
		{
			fdfs->step_x -= 5;
			fdfs->step_y += 5;
		}

		if (x > medx && y > medy) // 4
		{
			fdfs->step_x += 5;
			fdfs->step_y += 5;
		}


		fdfs->zoom -= ZOOM_STEP;
	}

	render_map(p);
	return (0);
}



void	move(void *param)
{
	t_fdfs	*fdfs = (t_fdfs *)param;
	if (mlx_is_key_down(fdfs->mlx, MLX_KEY_DOWN))
		fdfs->step_y += STEP;
	if (mlx_is_key_down(fdfs->mlx, MLX_KEY_UP))
		fdfs->step_y -= STEP;
	if (mlx_is_key_down(fdfs->mlx, MLX_KEY_RIGHT))
		fdfs->step_x += STEP;
	if (mlx_is_key_down(fdfs->mlx, MLX_KEY_LEFT))
		fdfs->step_x -= STEP;
	render_map(fdfs);
}

void	rotation(void *param)
{
	t_fdfs	*fdfs = (t_fdfs *)param;
	if (mlx_is_key_down(fdfs->mlx, MLX_KEY_S))
		fdfs->rotate_x += ROT_STEP;
	if (mlx_is_key_down(fdfs->mlx, MLX_KEY_W))
		fdfs->rotate_x -= ROT_STEP;
	if (mlx_is_key_down(fdfs->mlx, MLX_KEY_C))
		fdfs->rotate_y += ROT_STEP;
	if (mlx_is_key_down(fdfs->mlx, MLX_KEY_F))
		fdfs->rotate_y -= ROT_STEP;
	if (mlx_is_key_down(fdfs->mlx, MLX_KEY_A))
		fdfs->rotate_z += ROT_STEP;
	if (mlx_is_key_down(fdfs->mlx, MLX_KEY_D))
		fdfs->rotate_z -= ROT_STEP;
}

void	state(int keycode, t_fdfs *fdfs)
{
	if (keycode == KEY_J)
	{
		fdfs->state.map_color = 0;
		fdfs->state.rnd_color = !fdfs->state.rnd_color;
		set_palette(&fdfs->state.palette, 0);
	}
	if (keycode == KEY_M)
	{
		fdfs->state.rnd_color = 0;
		fdfs->state.map_color = !fdfs->state.map_color;
		set_palette(&fdfs->state.palette, 2);
	}

	if (keycode == KEY_0)
	{
		fdfs->state.disable_clean = !fdfs->state.disable_clean;
	}

	if (keycode == KEY_1)
	{
		fdfs->state.bg_color = !fdfs->state.bg_color;
		change_bgcolor(fdfs, random_color());
	}

	if (keycode == KEY_2)
	{
		fdfs->state.extra_pixel = !fdfs->state.extra_pixel;
	}

	if (keycode == KEY_3)
	{
		fdfs->state.multi_color = !fdfs->state.multi_color;
	}

	if (keycode == KEY_4)
	{
		fdfs->state.dark_zero = !fdfs->state.dark_zero;
	}

	if (keycode == KEY_5)
	{
		if (!fdfs->state.mirror)
			fdfs->state.mirror = 1;
		else
			fdfs->state.mirror = 0;
	}

	if (keycode == KEY_ENTER)
		fdfs->state.menu = !fdfs->state.menu;
}


void	ft_hook(void *param)
{
	t_fdfs	*fdfs;

	fdfs = (t_fdfs *)param;
	if (mlx_is_key_down(fdfs->mlx, MLX_KEY_R))
	{
		fdfs->state.map_color = 0;
		fdfs->state.rnd_color = 0;
		reset_fdfs(fdfs);
		//ft_bzero(fdfs->img->addr, WIN_W * WIN_H * (fdfs->img->bpp / 8));
	}
	if (mlx_is_key_down(fdfs->mlx, MLX_KEY_UP))
	{
		fdfs->step_y -= STEP;
	}
}

int	key_event(int keycode, t_fdfs *fdfs)
{
	if (keycode != KEY_ENTER)
		fdfs->state.menu = 0;
	if (keycode == KEY_ESC)
		close_win(fdfs);
	if (keycode == KEY_E || keycode == KEY_Q)
		zoom_and_altitude(keycode, fdfs);
	if (keycode == KEY_J || keycode == KEY_M || keycode == KEY_R
		|| keycode == KEY_ENTER || keycode == KEY_0 || keycode == KEY_1 || keycode == KEY_2 || keycode == KEY_3 || keycode == KEY_4 || keycode == KEY_5)
		state(keycode, fdfs);
	if (keycode == KEY_V || keycode == KEY_G)
		zoom_and_altitude(keycode, fdfs);
	if (keycode == KEY_T)
		fdfs->state.zenith = !fdfs->state.zenith;
	render_map(fdfs);
	if (fdfs->state.menu)
		show_menu(fdfs);
	return (0);
}
