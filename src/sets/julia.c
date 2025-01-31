/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:09:40 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/06 12:06:39 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fractol.h"
#define TWOP 6.28318530718
//c = init_vec2(0.3, 0.5);
//c = init_vec2(-1.417022285618,  0.0099534);
//c = init_vec2(–0.038088, 0.97);
//c = init_vec2(-0.8, 0.15);
//c = init_vec2(-0.4, 0.6);
static t_coord	julia_logic(t_env *env, t_coord act)
{
	t_coord	i;
	t_coord	c;
	t_coord	z;
	double	tmp;

	(void) act;
	c = init_vec2(env->z.x, env->z.y);
	z = init_vec2(act.x / env->size.z + env->plage.x1, \
	act.y / env->size.z + env->plage.y1);
	i.x = 0;
	while (z.x * z.x + z.y * z.y < env->limit && i.x < env->itelimit)
	{
		tmp = z.x;
		z.x = z.x * z.x - z.y * z.y + c.x;
		z.y = 2 * z.y * tmp + c.y;
		i.x++;
	}
	i.y = z.x * z.x + z.y * z.y;
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

void	*julia(t_env *env, t_coord act)
{
	t_coord	i;
	int		color;

	i = julia_logic(env, act);
	if (i.x != env->itelimit)
		color = gen_color(env, i);
	else
		color = rgba_to_hex(0, 0, 0, 0);
	put_color(env->addr, color, (act.y * env->line_length) + (act.x * 4));
	return NULL;
}
