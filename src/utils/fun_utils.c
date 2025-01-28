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
