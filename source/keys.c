/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/08/09 13:40:37 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

unsigned char	is_key_down;

void	mouse_scroll(double xdelta, double ydelta, void* param)
{
	t_fdfs	*fdfs = (t_fdfs *)param;
	is_key_down = 0;
	(void)xdelta;

	if (ydelta > 0)
		(fdfs->zoom -= ZOOM_STEP * 2) && (is_key_down = 1);
	else if (ydelta < 0)
		(fdfs->zoom += ZOOM_STEP * 2) && (is_key_down = 1);
	if (is_key_down)
		render_map(fdfs);
}

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


	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_RELEASE)
	{
		is_key_down = 1;
		fdfs->state.desplace = !fdfs->state.desplace;
	}

	if (keydata.key == MLX_KEY_ENTER && keydata.action == MLX_RELEASE)
	{
		is_key_down = 1;
		if (!fdfs->state.menu)
		{
			fdfs->state.menu = 1;
			fdfs->menu->enabled = false;
			render_menu(fdfs);
		}
		else
		{
			mlx_delete_image(fdfs->mlx, fdfs->menu);
			fdfs->state.menu = 0;
			fdfs->menu->enabled = true;
			if (mlx_image_to_window(fdfs->mlx, fdfs->img, 0, 0) < 0)
				error_and_exit("initialise_mlx", "mlx_image_to_window");
		}
	}

	if (keydata.key == MLX_KEY_P && keydata.action == MLX_RELEASE)
	{
		is_key_down = 0;
		fdfs->state.clon = !fdfs->state.clon;
	}
	if (fdfs->state.clon)
	{
		fdfs->rotate_x += ROT_STEP;
		render_map(fdfs);
		fdfs->rotate_x -= ROT_STEP;
		render_map(fdfs);
	}

	if (keydata.key == MLX_KEY_O && keydata.action == MLX_RELEASE)
	{
		is_key_down = 0;
		fdfs->state.live = !fdfs->state.live;
	}
	if (fdfs->state.live)
	{
		fdfs->step_y += 100;
		render_map(fdfs);
	}

	if (keydata.key == MLX_KEY_J && keydata.action == MLX_RELEASE)
	{
		is_key_down = 1;
		fdfs->state.rnd_color = !fdfs->state.rnd_color;
		if (fdfs->state.rnd_color)
		{
			set_palette(&fdfs->state.palette, 0);
		}
		else
		{
			set_palette(&fdfs->state.palette, 1);
		}
	}

	if (keydata.key == MLX_KEY_M && keydata.action == MLX_RELEASE)
	{
		is_key_down = 1;
		fdfs->state.map_color = !fdfs->state.map_color;
		if (fdfs->state.map_color)
		{
			set_palette(&fdfs->state.palette, 2);
		}
		else
		{
			set_palette(&fdfs->state.palette, 1);
		}
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
		if (fdfs->state.multi_color)
		{
			fdfs->state.multi_color = 0;
		}
		else
		{
			fdfs->state.multi_color = 1;
		}
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
		{
			fdfs->state.mirror = 1;
		}
		else
		{
			fdfs->state.mirror = 0;
		}
	}

	if (keydata.key == MLX_KEY_6 && keydata.action == MLX_RELEASE)
	{
		is_key_down = 1;
		if (fdfs->state.rnd_color)
		{
			fdfs->state.rnd_color = 0;
			set_palette(&fdfs->state.palette, 3);
		}
		else
		{
			fdfs->state.rnd_color = 1;
			set_palette(&fdfs->state.palette, 1);
		}
	}

	if (keydata.key == MLX_KEY_KP_0 && keydata.action == MLX_RELEASE)
	{
		is_key_down = 1;
		fdfs->state.mod_00 = !fdfs->state.mod_00;
	}

	if (keydata.key == MLX_KEY_KP_1 && keydata.action == MLX_RELEASE)
	{
		is_key_down = 1;
		fdfs->state.mod_01 = !fdfs->state.mod_01;
	}

	if (keydata.key == MLX_KEY_KP_2 && keydata.action == MLX_RELEASE)
	{
		is_key_down = 1;
		fdfs->state.mod_02 = !fdfs->state.mod_02;
	}

	if (keydata.key == MLX_KEY_KP_3 && keydata.action == MLX_RELEASE)
	{
		is_key_down = 1;
		fdfs->state.mod_03 = !fdfs->state.mod_03;
	}

	if (keydata.key == MLX_KEY_KP_4 && keydata.action == MLX_RELEASE)
	{
		is_key_down = 1;
		fdfs->state.mod_04 = !fdfs->state.mod_04;
	}

	if (keydata.key == MLX_KEY_R && keydata.action == MLX_RELEASE)
	{
		is_key_down = 1;
		reset_fdfs(fdfs);
	}

	if (keydata.key == MLX_KEY_T && keydata.action == MLX_RELEASE)
	{
		is_key_down = 1;
		fdfs->state.zenith = !fdfs->state.zenith;
	}

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(fdfs->mlx);

	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_RELEASE)
		(fdfs->zoom -= ZOOM_STEP) && (is_key_down = 1);
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_RELEASE)
		(fdfs->zoom += ZOOM_STEP) && (is_key_down = 1);
	if (keydata.key == MLX_KEY_G)
		(fdfs->flat += ALTITUDE_STEP) && (is_key_down = 1);
	if (keydata.key == MLX_KEY_V)
		(fdfs->flat -= ALTITUDE_STEP) && (is_key_down = 1);

	if (is_key_down)
		render_map(fdfs);
}
