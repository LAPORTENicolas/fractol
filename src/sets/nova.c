/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:09:40 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/06 14:16:57 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fractol.h"

static t_coord	nova_logic(t_env *env, t_coord act, double tmp, double tmp2)
{
	t_coord	i;
	t_coord	c;
	t_coord	z;
	t_coord	z3;

	c = init_vec2(act.x / env->size.z + env->plage.x1, \
	act.y / env->size.z + env->plage.y1);
	z = (t_coord){1., 0};
	i.x = 0;
	while (i.x < env->itelimit)
	{
		tmp = z.x;
		tmp2 = z.y;
		z3 = complex_mul(complex_mul(z, z), z);
		z3.x--;
		z = complex_add(complex_subtract(z, complex_div(z3, \
		complex_mul(complex_mul(z, z), (t_coord){3, 0}))), c);
		if (((z.x - tmp) * (z.x - tmp) + (z.y - tmp2) * (z.y - tmp2)) < 0.01)
			break ;
		i.x++;
	}
	return (i);
}

void	*nova(t_env *env, t_coord act)
{
	t_coord		i;
	t_coord3	color2;
	int			color;

	i = nova_logic(env, act, 0, 0);
	if (i.x != env->itelimit)
	{
		color2 = env->palette(i.x / env->itelimit);
		color = rgba_to_hex(color2.x * 255, \
		color2.y * 255, color2.z * 255, 255);
	}
	else
		color = rgba_to_hex(0, 0, 0, 0);
	put_color(env->addr, color, (act.y * env->line_length) + (act.x * 4));
	return NULL;
}
