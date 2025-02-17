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

static t_coord	mandelbrot_logic(t_env *env, t_coord act)
{
	t_coord	i;
	t_coord	c;
	t_coord	z;

	c = init_vec2(act.x / env->size.z + env->plage.x1, \
	act.y / env->size.z + env->plage.y1);
	z = (t_coord){0, 0};
	i.x = 0;
	while (z.x * z.x + z.y * z.y < 4 && i.x < env->itelimit)
	{
		z = complex_mul(z, z);
		z = complex_add(z, c);
		i.x++;
	}
	i.y = z.x * z.x + z.y * z.y;
	return (i);
}

void	mandelbrot(t_env *env, t_coord act)
{
	t_coord	i;
	int		color;

	i = mandelbrot_logic(env, act);
	if (i.x != env->itelimit)
		color = gen_color(env, i);
	else
		color = -16777216;
	put_color(env->addr, color, (act.y * env->line_length) + (act.x * 4));
}
