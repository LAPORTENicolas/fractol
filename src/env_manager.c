/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:57:11 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/06 15:52:12 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"
#include <mlx.h>

t_env	create_env(void)
{
	t_env	env;

	env.plage.x1 = -2;
	env.plage.x2 = 2;
	env.plage.y1 = -2;
	env.plage.y2 = 2;
	env.itelimit = 100;
	env.default_ssaa = 1;
	env.ssaa_coef = 2;
	env.z.x = 0.1;
	env.z.y = 0.7;
	env.tik = 0.;
	env.limit = 2;
	env.shift = 0;
	env.zoom.is_zoom = 0;
	env.pos = env.plage;
	env.type = NULL;
	env.palette = palette;
	env.mlx = mlx_init();
	return (env);
}

static void	edit_env2(t_env *env, int win)
{
	if (env->antialiasing)
	{
		if (win)
			env->size.z = 125 * env->ssaa_coef;
		env->size.x = (env->plage.x2 - env->plage.x1) * (env->size.z);
		env->size.y = (env->plage.y2 - env->plage.y1) * (env->size.z);
		if (win)
			env->win = mlx_new_window(env->mlx, env->size.x / env->ssaa_coef, \
			env->size.y / env->ssaa_coef, "Fractol");
	}
	else
	{
		if (win)
			env->size.z = 125;
		env->size.x = (env->plage.x2 - env->plage.x1) * env->size.z;
		env->size.y = (env->plage.y2 - env->plage.y1) * env->size.z;
		if (win)
			env->win = mlx_new_window(env->mlx, env->size.x, \
			env->size.y, "Fractol");
	}
}

t_env	create_from_env(t_env *env)
{
	env->antialiasing = !env->antialiasing;
	env->zoom.is_zoom = 0;
	if (env->antialiasing)
		env->size.z *= env->ssaa_coef;
	else
		env->size.z /= env->ssaa_coef;
	edit_env(env, 0);
	return (*env);
}

void	clear_env(t_env *env)
{
	if (env->img)
		mlx_destroy_image(env->mlx, env->img);
	if (env->antialiasing)
		mlx_destroy_image(env->mlx, env->img_r);
	mlx_destroy_window(env->mlx, env->win);
	mlx_destroy_display(env->mlx);
	free(env->mlx);
	exit(EXIT_SUCCESS);
}

void	edit_env(t_env *env, int win)
{
	edit_env2(env, win);

	if (env->antialiasing)
	{
		env->img = mlx_new_image(env->mlx, env->size.x, env->size.y);
		env->addr = mlx_get_data_addr(env->img, &env->bits_per_pixel, \
		&env->line_length, &env->endian);

		env->img_r = mlx_new_image(env->mlx, env->size.x / env->ssaa_coef, \
		env->size.y / env->ssaa_coef);
		env->addr_r = mlx_get_data_addr(env->img_r, &env->bits_per_pixel_r, \
		&env->line_length_r, &env->endian_r);
	}
	else
	{
		env->img = mlx_new_image(env->mlx, env->size.x, env->size.y);
		env->addr = mlx_get_data_addr(env->img, &env->bits_per_pixel, \
		&env->line_length, &env->endian);
	}
}
