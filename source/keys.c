/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/07/30 12:11:30 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

unsigned char	is_key_down;

void mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
	t_fdfs	*fdfs = (t_fdfs *)param;
	is_key_down = 0;

	(void)mods;
	if (button == MLX_MOUSE_BUTTON_LEFT)
		(fdfs->rotate_z += ROT_STEP) && (is_key_down = 1);
	if (button == MLX_MOUSE_BUTTON_RIGHT)
		(fdfs->rotate_z -= ROT_STEP) && (is_key_down = 1);
	if (button == MLX_MOUSE_BUTTON_MIDDLE && action == MLX_RELEASE)
		(fdfs->state.zenith = !fdfs->state.zenith) && (is_key_down = 1);
	if (is_key_down)
		render_map(fdfs);

/*

	if (mlx_is_mouse_down(fdfs->mlx, 0))
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

	if (mlx_is_mouse_down(fdfs->mlx, 0))
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


	(void)param;
	// Simple up or down detection.
	if (y > 0)
		printf("Up!");
	else if (y < 0)
		printf("Down!");

	// Can also detect a mousewheel that goes along the X (e.g: MX Master 3)
	if (x < 0)
		printf("Sliiiide to the left!");
	else if (x > 0)
		printf("Sliiiide to the right!");

		*/
}

void	zoom_and_altitude(void *param)
{
	t_fdfs	*fdfs = (t_fdfs *)param;
	is_key_down = 0;

	if (mlx_is_key_down(fdfs->mlx, MLX_KEY_Q) && fdfs->zoom > 0)
		(fdfs->zoom -= ZOOM_STEP) && (is_key_down = 1);
	if (mlx_is_key_down(fdfs->mlx, MLX_KEY_E) && fdfs->zoom < 100)
		(fdfs->zoom += ZOOM_STEP) && (is_key_down = 1);
	if (mlx_is_key_down(fdfs->mlx, MLX_KEY_G) && fdfs->flat < 50)
		(fdfs->flat += ALTITUDE_STEP) && (is_key_down = 1);
	if (mlx_is_key_down(fdfs->mlx, MLX_KEY_V) && fdfs->flat > -50)
		(fdfs->flat -= ALTITUDE_STEP) && (is_key_down = 1);
	if (is_key_down)
		render_map(fdfs);
}

void	move(void *param)
{
	t_fdfs	*fdfs = (t_fdfs *)param;
	is_key_down = 0;

	if (mlx_is_key_down(fdfs->mlx, MLX_KEY_DOWN))
		(fdfs->step_y += STEP) && (is_key_down = 1);
	if (mlx_is_key_down(fdfs->mlx, MLX_KEY_UP))
		(fdfs->step_y -= STEP) && (is_key_down = 1);
	if (mlx_is_key_down(fdfs->mlx, MLX_KEY_RIGHT))
		(fdfs->step_x += STEP) && (is_key_down = 1);
	if (mlx_is_key_down(fdfs->mlx, MLX_KEY_LEFT))
		(fdfs->step_x -= STEP) && (is_key_down = 1);
	if (is_key_down)
		render_map(fdfs);
}

void	rotation(void *param)
{
	t_fdfs	*fdfs = (t_fdfs *)param;
	is_key_down = 0;

	if (mlx_is_key_down(fdfs->mlx, MLX_KEY_S))
		(fdfs->rotate_x += ROT_STEP) && (is_key_down = 1);
	if (mlx_is_key_down(fdfs->mlx, MLX_KEY_W))
		(fdfs->rotate_x -= ROT_STEP) && (is_key_down = 1);
	if (mlx_is_key_down(fdfs->mlx, MLX_KEY_C))
		(fdfs->rotate_y += ROT_STEP) && (is_key_down = 1);
	if (mlx_is_key_down(fdfs->mlx, MLX_KEY_F))
		(fdfs->rotate_y -= ROT_STEP) && (is_key_down = 1);
	if (mlx_is_key_down(fdfs->mlx, MLX_KEY_A))
		(fdfs->rotate_z += ROT_STEP) && (is_key_down = 1);
	if (mlx_is_key_down(fdfs->mlx, MLX_KEY_D))
		(fdfs->rotate_z -= ROT_STEP) && (is_key_down = 1);
	if (is_key_down)
		render_map(fdfs);
}


void key_hook(mlx_key_data_t keydata, void* param)
{
	t_fdfs	*fdfs = (t_fdfs *)param;
	is_key_down = 0;

	if (keydata.key == MLX_KEY_ENTER && keydata.action == MLX_RELEASE)
	{
		is_key_down = 1;
		if (fdfs->state.menu)
		{
			fdfs->state.menu = 0;
			fdfs->menu->enabled = false;
		}
		else
		{
			fdfs->state.menu = 1;
			fdfs->menu->enabled = true;
		}
	}
	if (keydata.key == MLX_KEY_J && keydata.action == MLX_RELEASE)
	{
		is_key_down = 1;
		fdfs->state.map_color = 0;
		fdfs->state.rnd_color = !fdfs->state.rnd_color;
		set_palette(&fdfs->state.palette, 0);
	}
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_RELEASE)
	{
		is_key_down = 1;
		fdfs->state.rnd_color = 0;
		fdfs->state.map_color = !fdfs->state.map_color;
		set_palette(&fdfs->state.palette, 2);
	}

	if (keydata.key == MLX_KEY_0 && keydata.action == MLX_RELEASE)
	{
		is_key_down = 1;
		fdfs->state.disable_clean = !fdfs->state.disable_clean;
	}

	if (keydata.key == MLX_KEY_1 && keydata.action == MLX_RELEASE)
	{
		is_key_down = 1;
		if (fdfs->state.bg_color == 0x000000FF)
		{
			fdfs->state.bg_color = random_color();
			set_bgcolor(fdfs->img, fdfs->state.bg_color);
		}
		else
			fdfs->state.bg_color = 0x000000FF;
	}

	if (keydata.key == MLX_KEY_2 && keydata.action == MLX_RELEASE)
	{
		is_key_down = 1;
		fdfs->state.extra_pixel = !fdfs->state.extra_pixel;
	}

	if (keydata.key == MLX_KEY_3 && keydata.action == MLX_RELEASE)
	{
		is_key_down = 1;
		fdfs->state.multi_color = !fdfs->state.multi_color;
	}

	if (keydata.key == MLX_KEY_4 && keydata.action == MLX_RELEASE)
	{
		is_key_down = 1;
		fdfs->state.dark_zero = !fdfs->state.dark_zero;
	}

	if (keydata.key == MLX_KEY_5 && keydata.action == MLX_RELEASE)
	{
		is_key_down = 1;
		if (!fdfs->state.mirror)
			fdfs->state.mirror = 1;
		else
			fdfs->state.mirror = 0;
	}

	if (keydata.key == MLX_KEY_6 && keydata.action == MLX_RELEASE)
	{
		is_key_down = 1;
		if (!fdfs->state.one_color)
			fdfs->state.one_color = random_color();
		else
			fdfs->state.one_color = 0;
	}

	if (keydata.key == MLX_KEY_R && keydata.action == MLX_RELEASE)
	{
		is_key_down = 1;
		fdfs->state.map_color = 0;
		fdfs->state.rnd_color = 0;
		reset_fdfs(fdfs);
	}

	if (keydata.key == MLX_KEY_T && keydata.action == MLX_RELEASE)
	{
		is_key_down = 1;
		fdfs->state.zenith = !fdfs->state.zenith;
	}

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(fdfs->mlx);

	if (is_key_down)
		render_map(fdfs);
}
