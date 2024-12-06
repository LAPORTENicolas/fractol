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
			env->size.z = 125;
		env->size.x = ((env->plage.x2 - env->plage.x1) / 2) * (env->size.z * 2);
		env->size.y = ((env->plage.y2 - env->plage.y1) / 2) * (env->size.z * 2);
		if (win)
			env->win = mlx_new_window(env->mlx, env->size.x / ANTI, \
			env->size.y / ANTI, "Fractol");
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
	t_env	new;

	new.plage.x1 = env->plage.x1;
	new.plage.x2 = env->plage.x2;
	new.plage.y1 = env->plage.y1;
	new.plage.y2 = env->plage.y2;
	new.itelimit = env->itelimit;
	new.size.z = env->size.z;
	new.antialiasing = !env->antialiasing;
	new.z.x = env->z.x;
	new.z.y = env->z.y;
	new.tik = env->tik;
	new.limit = env->limit;
	new.shift = env->shift;
	new.zoom.is_zoom = 0;
	new.pos = new.plage;
	new.type = env->type;
	new.palette = env->palette;
	new.win = env->win;
	new.mlx = env->mlx;
	edit_env(&new, 0);
	return (new);
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
	env->img = mlx_new_image(env->mlx, env->size.x, env->size.y);
	env->addr = mlx_get_data_addr(env->img, &env->bits_per_pixel, \
		&env->line_length, &env->endian);
	if (env->antialiasing)
	{
		env->img_r = mlx_new_image(env->mlx, env->size.x / ANTI, \
		env->size.y / ANTI);
		env->addr_r = mlx_get_data_addr(env->img_r, &env->bits_per_pixel_r, \
		&env->line_length_r, &env->endian_r);
	}
}
