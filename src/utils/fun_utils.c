/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:51:14 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/06 12:57:49 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fractol.h"

double	ft_atof(char *s)
{
	double	atof;
	double	tmp;
	int		i;

	i = 10;
	atof = 0;
	if (s == NULL)
		return (0.);
	if (ft_isdigit(*s))
		atof += *s++ - '0';
	else
		return (0.);
	s++;
	while (*s && ft_isdigit(*s))
	{
		tmp = *s++ - '0';
		tmp /= i;
		atof += tmp;
		i *= 10;
	}
	return (atof);
}

double	ft_length(t_coord x)
{
	return (sqrt(x.x * x.x + x.y * x.y));
}

double	ft_min(double x, double y)
{
	if (x < y)
		return (x);
	return (y);
}
