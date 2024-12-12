/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:51:14 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/10 23:40:49 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fractol.h"

static int	get_sign(char **s)
{
	char	c;

	if (!s || !*s || !*(*s))
		return (1);
	c = *(*s);
	if (c == '-')
	{
		*(s) += 1;
		return (-1);
	}
	return (1);
}

double	ft_atof(char *s)
{
	double	atof;
	double	tmp;
	int		i;
	int		sign;

	i = 10;
	atof = 0;
	if (s == NULL)
		return (0.);
	sign = get_sign(&s);
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
	return (atof * sign);
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

void	free_buddha(t_env *env, t_coord3 **map)
{
	int	i;

	i = 0;
	while (i < env->size.x - 1)
	{
		ft_printf("i = %i/n", i);
		if (map[i])
			free(map[i]);
		i++;
	}
	free(map);
}
