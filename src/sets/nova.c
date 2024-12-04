/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nova.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:37:02 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/04 14:09:59 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fractol.h"

static t_coord	p(t_coord z)
{
	return (sub_vec2(mul_vec2(z, mul_vec2(z, z)), (t_coord){1., 1.}));
}

static t_coord	p_prime(t_coord z)
{
	return (mul_vec2((t_coord){3., 3.}, mul_vec2(z, z)));
}

void	nova_logic(t_env *env, t_coord act)
{
	t_coord	z;
	t_coord	beta;
	t_coord3 col;
	double	alpha;
	int	i;
	int pixel;

	z = (t_coord){act.x, act.y};
	beta = (t_coord){0., 0.};
	alpha = 1.;
	i = 0;
	while (i < env->limit && z.x * z.x + z.y * z.y < 4)
	{
		z = add_vec2(sub_vec2(z, mul_vec2((t_coord){alpha, 0.}, div_vec2(p(z), p_prime(z)))), beta);
		i++;
	}
	pixel = (act.y * env->line_length) + (act.x * 4);
	if (i == env->limit)
		put_color(env, rgba_to_hex(255, 255, 255, 255), pixel);
	else
	{
		if (env->shift)
			col = env->palette((i * env->tik) / 100);
		else
			col = env->palette((double)i / 100);
		put_color(env, rgba_to_hex(col.x, col.y, col.z, 255), pixel);
	}
}
