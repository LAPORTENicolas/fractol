/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:09:21 by nlaporte          #+#    #+#             */
/*   Updated: 2024/11/29 11:32:15 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fractol.h"

t_coord3	add_vec3(t_coord3 vec1, t_coord3 vec2)
{
	t_coord3	new;

	new.x = vec1.x + vec2.x;
	new.y = vec1.y + vec2.y;
	new.z = vec1.z + vec2.z;
	return (new);
}

t_coord3	umul_vec3(t_coord3 vec1, double m)
{
	t_coord3	new;

	new.x = vec1.x * m;
	new.y = vec1.y * m;
	new.z = vec1.z * m;
	return (new);
}

t_coord3	mul_vec3(t_coord3 vec1, t_coord3 vec2)
{
	t_coord3	new;

	new.x = vec1.x * vec2.x;
	new.y = vec1.y * vec2.y;
	new.z = vec1.z * vec2.z;
	return (new);
}

t_coord4	sub_vec4(t_coord4 vec1, t_coord4 vec2)
{
	t_coord4	new;

	new.x1 = vec1.x1 - vec2.x1;
	new.x2 = vec1.x2 - vec2.x2;
	new.y1 = vec1.y1 - vec2.y1;
	new.y2 = vec1.y2 - vec2.y2;
	return (new);
}

t_coord4	udiv_vec4(t_coord4 vec1, int div)
{
	t_coord4	new;

	new.x1 = vec1.x1 / div;
	new.x2 = vec1.x2 / div;
	new.y1 = vec1.y1 / div;
	new.y2 = vec1.y2 / div;
	return (new);
}
