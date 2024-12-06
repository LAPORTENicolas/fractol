/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newton.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:09:40 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/06 13:12:06 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fractol.h"
#include <math.h>

static t_n_point	get_newton_point(void)
{
	t_n_point	new;

	new.p1 = (t_coord){1.0, 0.0};
	new.p2 = (t_coord){-.5, .866};
	new.p3 = (t_coord){-.5, -.866};
	return (new);
}

static t_coord4	get_distance(t_coord c1, t_n_point c2)
{
	t_coord4	new;

	new.x1 = ft_length(complex_subtract(c1, c2.p1));
	new.x2 = ft_length(complex_subtract(c1, c2.p2));
	new.y1 = ft_length(complex_subtract(c1, c2.p3));
	new.y2 = ft_min(new.x1, ft_min(new.x2, new.y1));
	return (new);
}

static int	newton_logic2(t_env *env, t_n_point p, t_coord *c, t_coord4 *d)
{
	t_n_point	tmp;
	t_coord		denom;
	t_coord		z;
	int			i;

	i = 0;
	denom = (t_coord){0, 0};
	z = (t_coord){0, 0};
	while (d->y2 > 0.001 && i < env->itelimit)
	{
		z = complex_mul(complex_subtract(*c, p.p1), \
		complex_mul(complex_subtract(*c, p.p2), complex_subtract(*c, p.p3)));
		tmp.p1 = complex_mul(complex_subtract(*c, p.p2), \
		complex_subtract(*c, p.p3));
		tmp.p2 = complex_mul(complex_subtract(*c, p.p1), \
		complex_subtract(*c, p.p3));
		tmp.p3 = complex_mul(complex_subtract(*c, p.p1), \
		complex_subtract(*c, p.p2));
		denom = complex_add(tmp.p1, complex_add(tmp.p2, tmp.p3));
		*c = complex_subtract(*c, complex_div(z, denom));
		*d = get_distance(*c, p);
		i++;
	}
	return (i);
}

static t_coord4	newton_logic(t_env *env, t_coord act)
{
	t_n_point	p;
	t_coord4	d;
	t_coord		c;
	int			i;

	p = get_newton_point();
	i = 0;
	c = init_vec2(act.x / env->size.z + env->plage.x1, \
	act.y / env->size.z + env->plage.y1);
	d = get_distance(c, p);
	i = newton_logic2(env, p, &c, &d);
	return ((t_coord4){i, d.x1, d.x2, d.y1});
}

void	newton(t_env *env, t_coord act)
{
	t_coord4	res;
	int			color;

	res = newton_logic(env, act);
	if (res.x1 == env->itelimit)
		color = rgba_to_hex(0, 0, 0, 255);
	else if (res.x2 < res.y1 && res.x2 < res.y2)
		color = rgba_to_hex(255, 0, 0, 255);
	else if (res.y1 < res.y2)
		color = rgba_to_hex(0, 255, 0, 255);
	else
		color = rgba_to_hex(0, 0, 255, 255);
	put_color(env->addr, color, (act.y * env->line_length) + (act.x * 4));
	return ;
}
