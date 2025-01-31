/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:09:40 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/06 12:06:50 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fractol.h"

static t_coord	burning_ship_logic(t_env *env, t_coord act)
{
	t_coord	i;
	t_coord	c;
	t_coord	z;
	double	tmp;

	c = init_vec2(act.x / env->size.z + env->plage.x1, \
	act.y / env->size.z + env->plage.y1);
	z = init_vec2(0, 0);
	i.x = 0;
	while (z.x * z.x + z.y * z.y < env->limit && i.x < env->itelimit)
	{
		z.x = fabs(z.x);
		z.y = fabs(z.y);
		tmp = z.x;
		z.x = z.x * z.x - z.y * z.y + c.x;
		z.y = 2 * z.y * tmp + c.y;
		i.x++;
	}
	i.y = z.x * z.x + z.y * z.y;
	return (i);
}

void	*burning_ship(t_env *env, t_coord act)
{
	t_coord	i;
	int		color;

	i = burning_ship_logic(env, act);
	if (i.x != env->itelimit)
		color = gen_color(env, i);
	else
		color = rgba_to_hex(0, 0, 0, 0);
	put_color(env->addr, color, (act.y * env->line_length) + (act.x * 4));
	return NULL;
}
