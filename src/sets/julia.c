/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:09:40 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/04 11:40:37 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fractol.h"
#define TWOP 6.28318530718
//c = init_vec2(0.3, 0.5);
//c = init_vec2(-1.417022285618,  0.0099534);
//c = init_vec2(–0.038088, 0.97);
//c = init_vec2(-0.8, 0.15);
//c = init_vec2(-0.4, 0.6);
static int	julia_logic(t_env *env, t_coord act)
{
	t_coord		c;
	t_coord		z;
	double		tmp;
	int			i;

	(void) act;
	//c = init_vec2(env->z.x, env->z.y);
	c = init_vec2(-0.4, 0.6);
	z = init_vec2(act.x / env->size.z + env->plage.x1, \
	act.y / env->size.z + env->plage.y1);
	i = 0;
	while (z.x * z.x + z.y * z.y < env->limit && i < env->itelimit)
	{
		tmp = z.x;
		z.x = z.x * z.x - z.y * z.y + c.x;
		z.y = 2 * z.y * tmp + c.y;
		i++;
	}
	return (i);
}

void	init_anime_julia(t_env *env)
{
	env->z.x = -0.3;
	env->z.y = 1.;
	env->julia_target.x = 1;
	env->julia_target.y = 0;
	env->julia_anim = 1;
}

int	anime_julia(t_env *env)
{
	if (env->julia_anim == 0)
		return (0);
	if (env->julia_target.x > env->z.x)
		env->z.x += 0.002;
	if (env->julia_target.y < env->z.y)
		env->z.y -= 0.002;
	if (env->julia_target.x <= env->z.x || env->julia_target.y >= env->z.y)
		env->julia_anim = 0;
	render(env);
	return (1);
}

void	julia(t_env *env, t_coord act)
{
	t_coord3	tmp_col;
	int			color;
	int			i;

	i = julia_logic(env, act);
	if (i != env->itelimit)
	{
		if (env->shift)
			tmp_col = env->palette((i + env->tik) / env->itelimit);
		else
			tmp_col = env->palette((double)i / env->itelimit);
		color = rgba_to_hex(tmp_col.x * 255, tmp_col.y * 255, \
		tmp_col.z * 255, 255);
	}
	else
		color = rgba_to_hex(0, 0, 0, 0);
	put_color(env, color, (act.y * env->line_length) + (act.x * 4));
}
