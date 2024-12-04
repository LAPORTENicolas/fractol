/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buddhabrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:09:40 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/04 11:41:04 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fractol.h"

int	buddhabrot_logic(t_env *env, t_coord act)
{
	t_coord		c;
	t_coord		z;
	double		tmp;
	int			i;
	int			pixel;

	(void) pixel;
	pixel = (act.y * env->line_length) + (act.x * 4);
	c = init_vec2(act.x / env->size.z + env->plage.x1, \
	act.y / env->size.z + env->plage.y1);
	z = init_vec2(0, 0);
	i = 0;
	while (z.x * z.x + z.y * z.y < 4 && i < env->itelimit)
	{
		tmp = z.x;
		z.x = z.x * z.x - z.y * z.y + c.x;
		z.y = 2 * z.y * tmp + c.y;
		i++;
	}
	return (i);
}

void	buddhabrot(t_env *env, t_coord act)
{
	buddhabrot_logic(env, act);
	return ;
}
