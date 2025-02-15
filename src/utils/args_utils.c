/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:11:04 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/09 13:13:38 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fractol.h"

void	print_help(void)
{
	ft_printf("Usage: ./fractol -[options] [value]\n");
	ft_printf("Options:\n");
	ft_printf("	-h		: print all commands\n");
	ft_printf("	-t		: set type		[mandelbrot, \
julia, burning-s, newton, nova, \033[31mbuddhabrot\033[0m]\n");
	ft_printf("	-itel		: set iterationn limit \
 [1 - 3000]				(default: 100)\n");
	ft_printf("	-l		: set limit 		[2 - 10]\
				(default: 3)\n");
	ft_printf("	-c		: set color palette 	[1 \
- 6]					(default: 1)\n");
	ft_printf("	-z		: set complex number 	[double \
double] \033[93mONLY FOR JULIA !\033[0m	(default: 0.3 0.5)\n");
	ft_printf("	-shift		: set color shift enable \
					(default: disable)\n");
	ft_printf("	-size		: set window size \
						(default: 150 * 150)\n");
	ft_printf("	-debug		: Print log \
							(default: disable)\n");
	ft_printf("	-x		: set antialiasing multuplicator			\
	(default: 2x)\n");
	ft_printf("Use:\n");
	ft_printf("	ZQSD 		: For move\n");
	ft_printf("	Q 		: Enable SSAA. (Fixe cam pos)\n");
	ft_printf("	U	 	: decrease iteration limit\n");
	ft_printf("	Y		: increase iteration limit\n");
}

int	configure_itelimit(t_env *env, char *s)
{
	int	limit;

	if (s == NULL)
		return (-1);
	limit = ft_atoi(s);
	if ((limit <= 0 || limit >= 3001) && !env->buddhatakecontrol)
	{
		ft_printf("\033[31mIteration limit error:\
		bad value, try ./fractol -l [1 - 3000]\033[0m", 2);
		return (-1);
	}
	else if ((limit <= 200 || limit >= 2000000) && env->buddharender)
	{
		ft_printf("\033[31mIteration limit error:\
		bad value, try ./fractol -l [1 - 3000]\033[0m", 2);
		return (-1);
	}
	env->itelimit = limit;
	return (0);
}

int	configure_limit(t_env *env, char *s)
{
	int	limit;

	if (s == NULL)
		return (-1);
	limit = ft_atoi(s);
	if (limit <= 1 || limit >= 11)
	{
		ft_printf("\033[31mLimit error:\
		bad value, try ./fractol -l [2 - 10]\033[0m", 2);
		return (-1);
	}
	env->limit = limit;
	return (0);
}

int	configure_color(t_env *env, char *s)
{
	int	pal;

	pal = atoi(s);
	if (pal <= 0 || pal >= 7)
		return (-1);
	else if (pal == 1)
		env->palette = palette;
	else if (pal == 2)
		env->palette = palette2;
	else if (pal == 3)
		env->palette = palette3;
	else if (pal == 4)
		env->palette = palette4;
	else if (pal == 5)
		env->palette = palette5;
	else if (pal == 6)
		env->palette = palette6;
	env->paletteid = pal;
	return (0);
}

int     configure_z(t_env *env, char *s1, char *s2)
{
	double  *zx;
	double  *zy;

	printf("s1  %s\n", s1);
	zx = ft_atof(s1);
	zy = ft_atof(s2);
	printf("zx  %f\n", *zx);
	if (!zx || !*zx)
		return (-1);
	if (!zy || !*zy)
		return (-1);
	if (*zx > 10 || *zx < -10 || *zy > 10 || *zy < -10)
	{
		ft_printf("Bad val\n");
		free(zx);
		free(zy);
		return (-1);
	}
	env->z.x = *zx;
	env->z.y = *zy;
	free(zx);
	free(zy);
	return (0);
}
