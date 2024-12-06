/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_palette2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:05:30 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/06 12:00:59 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fractol.h"

t_coord3	palette7(double t)
{
	t_coord3	pale;
	t_coord3	a;
	t_coord3	b;
	t_coord3	c;
	t_coord3	d;

	a = (t_coord3){.500, 0.088, -2.472};
	b = (t_coord3){0.5, 0.5, 0.5};
	c = (t_coord3){0.333, 0.500, 0.333};
	d = (t_coord3){0.667, 0.500, 0.667};
	pale.x = a.x + b.x * cos(TWOP * (c.x * t + d.x));
	pale.y = a.y + b.y * cos(TWOP * (c.y * t + d.y));
	pale.z = a.z + b.z * cos(TWOP * (c.z * t + d.z));
	return (pale);
}

t_coord3	palette6(double t)
{
	t_coord3	pale;
	t_coord3	a;
	t_coord3	b;
	t_coord3	c;
	t_coord3	d;

	a = (t_coord3){.500, -0.272, -2.472};
	b = (t_coord3){0.5, 0.5, 0.5};
	c = (t_coord3){0.333, 0.500, 0.333};
	d = (t_coord3){0.667, 0.500, 0.667};
	pale.x = a.x + b.x * cos(TWOP * (c.x * t + d.x));
	pale.y = a.y + b.y * cos(TWOP * (c.y * t + d.y));
	pale.z = a.z + b.z * cos(TWOP * (c.z * t + d.z));
	return (pale);
}
