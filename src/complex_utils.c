/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:11:23 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/06 13:13:54 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

t_coord	complex_subtract(t_coord c1, t_coord c2)
{
	return ((t_coord){c1.x - c2.x, c1.y - c2.y});
}

t_coord	complex_mul(t_coord c1, t_coord c2)
{
	t_coord	new;

	new.x = (c1.x * c2.x) - (c1.y * c2.y);
	new.y = (c1.y * c2.x) + (c1.x * c2.y);
	return (new);
}

t_coord	complex_add(t_coord c1, t_coord c2)
{
	return ((t_coord){c1.x + c2.x, c1.y + c2.y});
}

t_coord	complex_div(t_coord c1, t_coord c2)
{
	t_coord	new;
	double	denom;

	denom = c2.x * c2.x + c2.y * c2.y;
	if (denom == 0)
		return ((t_coord){0, 0});
	new.x = (c1.x * c2.x + c1.y * c2.y) / denom;
	new.y = (c1.y * c2.x - c1.x * c2.y) / denom;
	return (new);
}
