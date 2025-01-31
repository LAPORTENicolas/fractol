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
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

void	render_buddha(t_env *env);

int	loop_hook(t_env *env)
{
	if (env->zoom.is_zoom)
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

void	*sous_render(void *arg)
{
	t_argF *arg_decode = (t_argF *) arg;
	t_coord	fork;

	fork = (t_coord){arg_decode->act.x, arg_decode->act.y};
	while (fork.x <= arg_decode->act.x + BLOCK_SIZE)
	{
		fork.y = arg_decode->act.y;
		while (fork.y <= arg_decode->act.y + BLOCK_SIZE)
		{
			arg_decode->env.type(&arg_decode->env, (t_coord){fork.x, fork.y});
			fork.y++;
		}
		fork.x++;
	}
	free(arg);
	return NULL;
}

void render(t_env *env)
{
	t_coord act;
	int i;
	pthread_t thread[PROC + 1];
	int process;

	i = 0;
	process = 0;
	act.x = 0;
	while (act.x < env->size.x)
	{
		act.y = 0;
		while (act.y < env->size.y)
		{
			t_argF *arg = malloc(sizeof(t_argF));
			arg->env = *env;
			arg->act = act;
			if (process >= PROC - 1)
			{
				while (i < process)
					pthread_join(thread[i++], NULL);
				process = 0;
				i = 0;
			}
			if (process < PROC)
			{
				pthread_create(&thread[process++], NULL, sous_render, arg);
			}
			act.y+= BLOCK_SIZE;
		}
		act.x+= BLOCK_SIZE;
	}
	while (i < process)
		pthread_join(thread[i++], NULL);
	env->tik++;
	if (env->antialiasing)
	{
		antialiasing_ssaa(env);
		mlx_put_image_to_window(env->mlx, env->win, env->img_r, 0, 0);
		return ;
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return ;
}

void	render2(t_env *env)
{
	t_coord	act;

	if (env->fractalid == 1)
		return render2(env);
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
