/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:08:35 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/04 12:41:42 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <libft.h>
#include <mlx.h>
#include <stdio.h>

void	render(t_env *env)
{
	t_coord	act;

	while (act.x < env->size.x)
	{
		act.y = 0;
		while (act.y < env->size.y)
		{
			env->type(env, act);
			act.y++;
		}
		act.x++;
	}
	env->tik += .4;
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}

int	loop_hook(t_env *env)
{
	if (env->zoom.is_zoom)
		ft_smoothscroll(env);
	render(env);
	return (0);
}

t_env	create_env(void)
{
	t_env	env;

	env.size.z = 100;
	env.plage.x1 = -2;
	env.plage.x2 = 2;
	env.plage.y1 = -2;
	env.plage.y2 = 2;
	env.itelimit = 100;
	env.z.x = 0.1;
	env.z.y = 0.7;
	env.tik = 0.;
	env.limit = 2;
	env.shift = 0;
	env.zoom.is_zoom = 0;
	env.pos = env.plage;
	env.type = NULL;
	env.palette = palette;
	env.size.x = (env.plage.x2 - env.plage.x1) * env.size.z;
	env.size.y = (env.plage.y2 - env.plage.y1) * env.size.z;
	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, env.size.x, env.size.y, "Fractol");
	env.img = mlx_new_image(env.mlx, env.size.x, env.size.y);
	env.addr = mlx_get_data_addr(env.img, &env.bits_per_pixel, \
		&env.line_length, &env.endian);
	return (env);
}

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

int	main(int ac, char **av)
{
	t_env	env;

	env = create_env();
	if (args_manager(ac, av, &env) != 0)
		return (-1);
	render(&env);
	mlx_hook(env.win, 4, 1L << 2, mouse_handler, &env);
	mlx_hook(env.win, 2, 5, keyboard_handler, &env);
	mlx_loop_hook(env.mlx, loop_hook, &env);
	mlx_loop(env.mlx);
	return (0);
}
