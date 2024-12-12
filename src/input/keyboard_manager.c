/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:14:32 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/09 14:08:48 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fractol.h"
#include <mlx.h>
#include <stdio.h>

static void	check_move(int button, t_env *env)
{
	t_coord	tmp;

	tmp.x = env->plage.x1 - env->plage.x2;
	tmp.y = env->plage.y1 - env->plage.y2;
	if (button == 119 && !env->antialiasing && !env->buddhatakecontrol)
	{
		env->plage.y1 += (tmp.x + tmp.y) / 40;
		env->plage.y2 += (tmp.x + tmp.y) / 40;
	}
	else if (button == 97 && !env->antialiasing && !env->buddhatakecontrol)
	{
		env->plage.x1 += (tmp.x + tmp.y) / 40;
		env->plage.x2 += (tmp.x + tmp.y) / 40;
	}
	else if (button == 115 && !env->antialiasing && !env->buddhatakecontrol)
	{
		env->plage.y1 -= (tmp.x + tmp.y) / 40;
		env->plage.y2 -= (tmp.x + tmp.y) / 40;
	}
	else if (button == 100 && !env->antialiasing && !env->buddhatakecontrol)
	{
		env->plage.x1 -= (tmp.x + tmp.y) / 40;
		env->plage.x2 -= (tmp.x + tmp.y) / 40;
	}
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

static void	screen_shot_key(t_env *env)
{
	int	x;
	int	y;

	x = (env->plage.x2 - env->plage.x1) * env->size.z;
	y = (env->plage.y2 - env->plage.y1) * env->size.z;
	if (!env->antialiasing)
		return ;
	screen_shot(env, env->img_r, \
	x / env->ssaa_coef, y / env->ssaa_coef);
}

int	keyboard_handler(int button, t_env *env)
{
	if (button == 65307)
		clear_env(env);
	check_move(button, env);
	if (button == 65362 && env->itelimit < 3000 && !env->buddhatakecontrol)
	{
		if (env->print_debug)
			ft_printf("New iteration limit = %i\n", env->itelimit);
		env->itelimit += 10;
	}
	else if (button == 65364 && env->itelimit > 10 && !env->buddhatakecontrol)
	{
		if (env->print_debug)
			ft_printf("New iteration limit = %i\n", env->itelimit);
		env->itelimit -= 10;
	}
	else if (button == 113)
		*env = switch_anti(env);
	else if (button == 99)
		screen_shot_key(env);
	if (!env->buddhatakecontrol)
		render(env);
	return (0);
}
