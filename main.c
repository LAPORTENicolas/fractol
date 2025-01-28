/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:08:35 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/11 18:36:51 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	render_buddha(t_env *env);

int	loop_hook(t_env *env)
{
	if (env->zoom.is_zoom && !env->antialiasing)
	{
		ft_smoothscroll(env);
		render(env);
	}
	else if (env->buddhatakecontrol && !env->buddharender)
		render_buddha(env);
	else if (!env->buddhatakecontrol)
		render(env);
	return (0);
}

static t_env	switch_anti(t_env *env)
{
	if (env->img)
		mlx_destroy_image(env->mlx, env->img);
	if (env->antialiasing)
		mlx_destroy_image(env->mlx, env->img_r);
	*env = create_from_env(env);
	if (env->print_debug)
		ft_printf("Antialiasing = %i x%i\n", env->antialiasing, env->ssaa_coef);
	if (env->buddhatakecontrol)
		env->buddharender = 0;
	return (*env);
}

void	render_buddha(t_env *env)
{
	t_coord3	**tmp_map;
	t_coord		act;

	*env = switch_anti(env);
	tmp_map = get_tmp_map(env->size.x, env->size.y);
	act.x = 0;
	while (act.x < env->size.x)
	{
		act.y = 0;
		while (act.y < env->size.y)
		{
			buddhabrot(env, act, tmp_map);
			act.y++;
		}
		act.x++;
	}
	env->tik++;
	buddhaconvertor(env, tmp_map);
	rotate_buddha(env);
	print_buddha(env);
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
	env->tik++;
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
	if (args_manager(ac, av, &env) != 0)
		return (-1);
	env.mlx = mlx_init();
	edit_env(&env, 1);
	if (env.buddhatakecontrol)
		render_buddha(&env);
	else
		render(&env);
	mlx_hook(env.win, 4, 1L << 2, mouse_handler, &env);
	mlx_hook(env.win, 2, 5, keyboard_handler, &env);
	mlx_loop_hook(env.mlx, loop_hook, &env);
	mlx_loop(env.mlx);
	return (0);
}
