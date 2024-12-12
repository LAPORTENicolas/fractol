/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssaa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:53:13 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/06 12:07:42 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fractol.h"

int	get_new_color(t_env *env, t_coord a)
{
	t_coord		t;
	t_coord3	tmp_color;
	t_coord3	color;
	int			diviseur;

	t = (t_coord){0, 0};
	color = (t_coord3){0, 0, 0};
	diviseur = 0;
	while (t.x < env->ssaa_coef && t.x + a.x < env->size.x)
	{
		t.y = 0;
		while (t.y < env->ssaa_coef && t.y + a.y < env->size.y)
		{
			tmp_color = get_pixel_color(env, env->addr, t.x + a.x, t.y + a.y);
			color = add_vec3(color, tmp_color);
			diviseur++;
			t.y++;
		}
		t.x++;
	}
	color = div_vec3(color, diviseur);
	return (rgba_to_hex(color.x, color.y, color.z, 255));
}

void	antialiasing_ssaa(t_env *env)
{
	t_coord	big;
	t_coord	litle;
	int		color;
	int		pixel;

	big = (t_coord){0, 0};
	litle = (t_coord){0, 0};
	while (big.x < env->size.x)
	{
		big.y = 0;
		litle.y = 0;
		while (big.y < env->size.y)
		{
			pixel = (litle.y * env->line_length_r) + (litle.x * 4);
			color = get_new_color(env, big);
			put_color(env->addr_r, color, pixel);
			big.y += env->ssaa_coef;
			litle.y++;
		}
		big.x += env->ssaa_coef;
		litle.x++;
	}
}
