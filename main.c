/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:08:35 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/06 15:33:15 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <libft.h>
#include <mlx.h>

int	loop_hook(t_env *env)
{
	if (env->zoom.is_zoom && !(!env->default_ssaa && env->antialiasing))
		ft_smoothscroll(env);
	render(env);
	return (0);
}

void	render(t_env *env)
{
	t_coord	act;

	act.x = 0;
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
	if (env->antialiasing)
	{
		antialiasing_ssaa(env);
		mlx_put_image_to_window(env->mlx, env->win, env->img_r, 0, 0);
		return ;
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}

int	main(int ac, char **av)
{
	t_env	env;

	env = create_env();
	env.antialiasing = 0;
	env.ac = ac;
	env.av = av;
	if (args_manager(ac, av, &env) != 0)
		return (-1);
	edit_env(&env, 1);
	render(&env);

	mlx_hook(env.win, 4, 1L << 2, mouse_handler, &env);
	mlx_hook(env.win, 2, 5, keyboard_handler, &env);
	mlx_loop_hook(env.mlx, loop_hook, &env);
	mlx_loop(env.mlx);
	return (0);
}
