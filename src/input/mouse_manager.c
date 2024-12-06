/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:29:51 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/06 15:49:07 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fractol.h"
#include <stdio.h>

static double	get_scale(int button)
{
	if (button == 5)
		return (1.4);
	else if (button == 4)
		return (1 / 1.4);
	return (-1);
}

int	ft_smoothscroll(t_env *env)
{
	double		scale;
	t_coord4	dif;

	dif = (t_coord4){env->zoom.neww.x - env->plage.x1, \
		env->plage.x2 - env->zoom.neww.x, env->zoom.neww.y - env->plage.y1,
		env->plage.y2 - env->zoom.neww.y};
	if (env->zoom.is_zoom == 0)
		return (0);
	env->zoom.act += env->zoom.step;
	if ((env->zoom.step > 0 && env->zoom.act >= env->zoom.target)
		|| (env->zoom.step < 0 && env->zoom.act <= env->zoom.target))
	{
		env->zoom.act = env->zoom.target;
		env->zoom.is_zoom = 0;
	}
	scale = env->size.z / env->zoom.act;
	env->plage.x1 = env->zoom.neww.x - dif.x1 * scale;
	env->plage.x2 = env->zoom.neww.x + dif.x2 * scale;
	env->plage.y1 = env->zoom.neww.y - dif.y1 * scale;
	env->plage.y2 = env->zoom.neww.y + dif.y2 * scale;
	env->size.z /= scale;
	if (env->zoom.is_zoom)
		return (1);
	return (0);
}

static void	configure_zoom(t_env *env, int x, int y, t_coord dif)
{
	if (env->antialiasing)
	{
		env->zoom.neww.x = env->plage.x1 + \
		(x / ((double)env->size.x / env->ssaa_coef)) * dif.x;
		env->zoom.neww.y = env->plage.y1 + \
		(y / ((double)env->size.y / env->ssaa_coef)) * dif.y;
		env->zoom.neww.x = env->plage.x1 + \
		(x / ((double)env->size.x / env->ssaa_coef)) * dif.x;
		env->zoom.neww.y = env->plage.y1 + \
		(y / ((double)env->size.y / env->ssaa_coef)) * dif.y;
		return ;
	}
	env->zoom.neww.x = env->plage.x1 + (x / (double)env->size.x) * dif.x;
	env->zoom.neww.y = env->plage.y1 + (y / (double)env->size.y) * dif.y;
	env->zoom.neww.x = env->plage.x1 + (x / (double)env->size.x) * dif.x;
	env->zoom.neww.y = env->plage.y1 + (y / (double)env->size.y) * dif.y;
}

int	mouse_handler(int button, int x, int y, t_env *env)
{
	double	scale;
	t_coord	dif;

	dif = (t_coord){env->plage.x2 - env->plage.x1, \
	env->plage.y2 - env->plage.y1};
	scale = get_scale(button);
	if (scale == -1)
		return (0);
	if (env->antialiasing)
		env->zoom.target = env->size.z / scale;
	else
		env->zoom.target = env->size.z / scale;
	env->zoom.step = (env->zoom.target - env->zoom.act) / 6.;
	configure_zoom(env, x, y, dif);
	env->zoom.is_zoom = 1;
	return (0);
}
