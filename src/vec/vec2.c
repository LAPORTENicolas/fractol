/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:09:21 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/04 14:00:37 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fractol.h"

t_coord	init_vec2(double x, double y)
{
	t_coord	new;

	new.x = x;
	new.y = y;
	return (new);
}

t_coord	add_vec2(t_coord vec1, t_coord vec2)
{
	t_coord	new;

	new.x = vec1.x + vec2.x;
	new.y = vec1.y + vec2.y;
	return (new);
}

t_coord	sub_vec2(t_coord vec1, t_coord vec2)
{
	t_coord new;

	new.x = vec1.x - vec2.x;
	new.y = vec1.y - vec2.y;
	return (new);
}

t_coord	div_vec2(t_coord vec1, t_coord vec2)
{
	t_coord new;

	new.x = vec1.x / vec2.x;
	new.y = vec1.y / vec2.y;
	return (new);
}

t_coord	mul_vec2(t_coord vec1, t_coord vec2)
{
	t_coord	new;

	new.x = vec1.x * vec2.x;
	new.y = vec1.y * vec2.y;
	return (new);
}
