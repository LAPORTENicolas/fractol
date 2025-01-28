/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:57:11 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/09 13:52:16 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

static void	buddha_mode(t_env *env)
{
	if (env->antialiasing)
	{
		env->size.z = env->default_size * env->ssaa_coef;
		env->size.y = (env->plage.x2 - env->plage.x1) * (env->size.z);
		env->size.x = (env->plage.y2 - env->plage.y1) * (env->size.z);
		env->win = mlx_new_window(env->mlx, env->size.x / env->ssaa_coef, \
		env->size.y / env->ssaa_coef, "Fractol");
	}
	else
	{
		env->size.z = env->default_size;
		env->size.y = (env->plage.x2 - env->plage.x1) * env->size.z;
		env->size.x = (env->plage.y2 - env->plage.y1) * env->size.z;
		env->win = mlx_new_window(env->mlx, env->size.x, \
		env->size.y, "Fractol");
	}
}

static void	edit_env2(t_env *env, int win)
{
	if (env->buddhatakecontrol)
		return (buddha_mode(env));
	if (env->antialiasing)
	{
		if (win)
			env->size.z = env->default_size * env->ssaa_coef;
		env->size.x = (env->plage.x2 - env->plage.x1) * (env->size.z);
		env->size.y = (env->plage.y2 - env->plage.y1) * (env->size.z);
		if (win)
			env->win = mlx_new_window(env->mlx, env->size.x / env->ssaa_coef, \
			env->size.y / env->ssaa_coef, "Fractol");
	}
	else
	{
		if (win)
			env->size.z = env->default_size;
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
	if (env->file_name)
		free(env->file_name);
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
