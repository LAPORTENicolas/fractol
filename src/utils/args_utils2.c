/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:15:48 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/10 23:46:25 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fractol.h"

static int	configure_set2(t_env *env, char *s)
{
	if (s && ft_strncmp(s, "buddhabrot", ft_strlen("buddhabrot") + 1) == 0)
	{
		env->buddhatakecontrol = 1;
		env->buddharender = 1;
		env->plage.x1 = -2.1;
		env->plage.x2 = 0.6;
		env->plage.y1 = -1.2;
		env->plage.y2 = 1.2;
		return (0);
	}
	else if (s && ft_strncmp(s, "newton", ft_strlen("newton") + 1) == 0)
	{
		env->type = newton;
		env->fractalid = 4;
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
		env->fractalid = 1;
	}
	else if (s && ft_strncmp(s, "julia", ft_strlen("julia") + 1) == 0)
	{
		env->type = julia;
		env->fractalid = 2;
	}
	else if (s && ft_strncmp(s, "nova", ft_strlen("nova") + 1) == 0)
	{
		env->type = nova;
		env->fractalid = 5;
	}
	else if (s && ft_strncmp(s, "burning-s", ft_strlen("burning-s") + 1) == 0)
	{
		env->type = burning_ship;
		env->fractalid = 3;
	}
	else if (configure_set2(env, s) == 0)
		return (0);
	else
		return (-1);
	return (0);
}

int	check_type(char **av, t_env *env, int i)
{
	if (configure_set(env, av[i]) != -1)
		return (0);
	return (-1);
}

int	configure_ssaa(t_env *env, char *s)
{
	int	r;

	if (!s)
		return (-1);
	r = ft_atoi(s);
	if (r <= 1)
		return (-1);
	env->ssaa_coef = r;
	return (0);
}
