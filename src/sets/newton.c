/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:09:40 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/03 23:08:26 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fractol.h"
#include <math.h>

t_coord complex_subtract(t_coord c1, t_coord c2)
{
	return ((t_coord){c1.x - c2.x, c1.y - c2.y});
}

t_coord	complex_mul(t_coord c1, t_coord c2)
{
	t_coord new;

	new.x = (c1.x * c2.x) - (c1.y * c2.y);
	new.y = (c1.y * c2.x) + (c1.x * c2.y);
	return (new);
}

double	ft_length(t_coord x)
{
	return (sqrt(x.x * x.x + x.y * x.y));
}

double	ft_min(double x, double y)
{
	if (x < y)
		return (x);
	return (y);
}

static t_coord	newton_logic(t_env *env, t_coord act)
{
	t_coord		c;
	t_coord		z;
	int		i;
	t_coord		p1 = {0., .5};
	t_coord		p2 = {.5, -.5};
	t_coord		p3 = {-.5, -.5};
	double		tmp;
	double		min;
	double		limit = 0.001;

	c = init_vec2(act.x / env->size.z + env->plage.x1, \
	act.y / env->size.z + env->plage.y1);
	z = init_vec2(0, 0);

	double d_1 = ft_length(complex_subtract(c, p1));
	double d_2 = ft_length(complex_subtract(c, p2));
	double d_3 = ft_length(complex_subtract(c, p3));
	double d_min = ft_min(d_1, ft_min(d_2, d_3));
	
	while (min < limit && i < env->itelimit)
	{
	}
	return (i);
}

void	newton(t_env *env, t_coord act)
{
	t_coord3	tmp_col;
	t_coord		i;
	int			color;

	i = mandelbrot_logic(env, act);
	if (i.x != env->itelimit)
	{
		if (env->shift)
			tmp_col = env->palette((i.x + env->tik) / env->itelimit);
		else
			tmp_col = env->palette(i.x / env->itelimit);
		color = rgba_to_hex(tmp_col.x * 255, tmp_col.y * 255, \
		tmp_col.z * 255, 255);
	}
	else
		color = rgba_to_hex(0, 0, 0, 0);
	put_color(env, color, (act.y * env->line_length) + (act.x * 4));
}
