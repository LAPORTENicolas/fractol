/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:15:48 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/06 13:38:15 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fractol.h"
#include <ctype.h>

static int	configure_set2(t_env *env, char *s)
{
	if (s && ft_strncmp(s, "buddhabrot", ft_strlen("buddhabrot") + 1) == 0)
	{
		env->type = buddhabrot;
		return (0);
	}
	else if (s && ft_strncmp(s, "nova", ft_strlen("nova") + 1) == 0)
	{
		env->type = nova;
		return (0);
	}
	else if (s && ft_strncmp(s, "newton", ft_strlen("newton") + 1) == 0)
	{
		env->type = newton;
		return (0);
	}
	return (-1);
}

int	check_z(int ac, char **av, t_env *env, int i)
{
	(void)ac;
	if (ft_strncmp(av[i], "-z", ft_strlen("-z") + 1) == 0)
	{
		if (configure_z(env, av[i + 1], av[i + 2]) == -1)
			return (-1);
		else
			return (0);
	}
	return (-1);
}

int	configure_set(t_env *env, char *s)
{
	if (s && ft_strncmp(s, "mandelbrot", ft_strlen("mandelbrot") + 1) == 0)
	{
		env->type = mandelbrot;
		return (0);
	}
	else if (s && ft_strncmp(s, "julia", ft_strlen("julia") + 1) == 0)
	{
		env->type = julia;
		return (0);
	}
	else if (s && ft_strncmp(s, "burning-s", ft_strlen("burning-s") + 1) == 0)
	{
		env->type = burning_ship;
		return (0);
	}
	else if (configure_set2(env, s) == 0)
		return (0);
	ft_putendl_fd("\033[31mType error:\
	bad name, try ./fractol -t mandelbrot\033[0m", 2);
	return (-1);
}
