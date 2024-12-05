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

static t_coord	mandelbrot_logic(t_env *env, t_coord act)
{
	t_coord		c;
	t_coord		z;
	t_coord		i;
	double		tmp;

	c = init_vec2(act.x / env->size.z + env->plage.x1, \
	act.y / env->size.z + env->plage.y1);
	z = init_vec2(0, 0);
	i.x = 0;
	while (z.x * z.x + z.y * z.y < env->limit && i.x < env->itelimit)
	{
		tmp = z.x;
		z.x = z.x * z.x - z.y * z.y + c.x;
		z.y = 2 * z.y * tmp + c.y;
		i.x++;
	}
	i.y = z.x * z.x + z.y + z.y;
	return (i);
}

void	mandelbrot(t_env *env, t_coord act)
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
