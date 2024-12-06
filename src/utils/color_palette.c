/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_palette.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:48:28 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/06 12:00:25 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fractol.h"

t_coord3	palette(double t)
{
	t_coord3	pale;
	t_coord3	a;
	t_coord3	b;
	t_coord3	c;
	t_coord3	d;

	a = (t_coord3){0.5, 0.5, 0.5};
	b = (t_coord3){0.5, 0.5, 0.5};
	c = (t_coord3){1, 1, 1};
	d = (t_coord3){0.0, 0.33, 0.67};
	pale.x = a.x + b.x * cos(TWOP * (c.x * t + d.x));
	pale.y = a.y + b.y * cos(TWOP * (c.y * t + d.y));
	pale.z = a.z + b.z * cos(TWOP * (c.z * t + d.z));
	return (pale);
}

t_coord3	palette2(double t)
{
	t_coord3	pale;
	t_coord3	a;
	t_coord3	b;
	t_coord3	c;
	t_coord3	d;

	a = (t_coord3){0.5, 0.5, 0.5};
	b = (t_coord3){0.5, 0.5, 0.5};
	c = (t_coord3){1, 1, 1};
	d = (t_coord3){0.30, 0.20, 0.20};
	pale.x = a.x + b.x * cos(TWOP * (c.x * t + d.x));
	pale.y = a.y + b.y * cos(TWOP * (c.y * t + d.y));
	pale.z = a.z + b.z * cos(TWOP * (c.z * t + d.z));
	return (pale);
}

t_coord3	palette3(double t)
{
	t_coord3	pale;
	t_coord3	a;
	t_coord3	b;
	t_coord3	c;
	t_coord3	d;

	a = (t_coord3){0.51, 0.51, 0.51};
	b = (t_coord3){0.495, 0.495, 0.495};
	c = (t_coord3){0.81, 0.81, 0.81};
	d = (t_coord3){-.692, -.592, -.492};
	pale.x = a.x + b.x * cos(TWOP * (c.x * t + d.x));
	pale.y = a.y + b.y * cos(TWOP * (c.y * t + d.y));
	pale.z = a.z + b.z * cos(TWOP * (c.z * t + d.z));
	return (pale);
}

t_coord3	palette4(double t)
{
	t_coord3	pale;
	t_coord3	a;
	t_coord3	b;
	t_coord3	c;
	t_coord3	d;

	a = (t_coord3){0.5, 0.5, 0.5};
	b = (t_coord3){0.5, 0.5, 0.5};
	c = (t_coord3){2.0, 1.0, 0.0};
	d = (t_coord3){0.50, 0.20, 0.25};
	pale.x = a.x + b.x * cos(TWOP * (c.x * t + d.x));
	pale.y = a.y + b.y * cos(TWOP * (c.y * t + d.y));
	pale.z = a.z + b.z * cos(TWOP * (c.z * t + d.z));
	return (pale);
}

t_coord3	palette5(double t)
{
	t_coord3	pale;
	t_coord3	a;
	t_coord3	b;
	t_coord3	c;
	t_coord3	d;

	a = (t_coord3){0., 0.5, 0.5};
	b = (t_coord3){0., 0.5, 0.5};
	c = (t_coord3){0., 0.5, 0.333};
	d = (t_coord3){0.0, 0.50, 0.667};
	pale.x = a.x + b.x * cos(TWOP * (c.x * t + d.x));
	pale.y = a.y + b.y * cos(TWOP * (c.y * t + d.y));
	pale.z = a.z + b.z * cos(TWOP * (c.z * t + d.z));
	return (pale);
}
