/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:34:40 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/11 18:35:41 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fractol.h"

void	print_buddha(t_env *env)
{
	if (env->antialiasing)
	{
		antialiasing_ssaa(env);
		env->buddharender = 1;
		mlx_put_image_to_window(env->mlx, env->win, env->img_r, 0, 0);
		return ;
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	env->buddharender = 1;
}

t_env	create_env(void)
{
	t_env	env;

	env.plage = (t_coord4){-2, 2, -2, 2};
	env.file_name = NULL;
	env.screen_nb = 0;
	env.itelimit = 100;
	env.antialiasing = 0;
	env.buddhatakecontrol = 0;
	env.default_ssaa = 0;
	env.ssaa_coef = 2;
	env.default_size = 40;
	env.z = (t_coord){0.3, 0.5};
	env.tik = 0.;
	env.limit = 2;
	env.shift = 0;
	env.zoom.is_zoom = 0;
	env.zoom.step = 0;
	env.zoom.act = 0;
	env.zoom.target = 0;
	env.print_debug = 0;
	env.pos = env.plage;
	env.type = NULL;
	env.palette = palette;
	return (env);
}

t_coord3	palette6(double t)
{
	t_coord3	pale;
	t_coord3	a;
	t_coord3	b;
	t_coord3	c;
	t_coord3	d;

	a = (t_coord3){0., 0.5, 0.5};
	b = (t_coord3){0., 0.5, 0.5};
	c = (t_coord3){0., 0.5, 0.333};
	d = (t_coord3){0.0, 0.50, 0.667};
	pale.x = a.x + b.x * cos(TWOP * (c.x * t + d.x));
	pale.y = a.y + b.y * cos(TWOP * (c.y * t + d.y));
	pale.z = a.z + b.z * cos(TWOP * (c.z * t + d.z));
	return (pale);
}
