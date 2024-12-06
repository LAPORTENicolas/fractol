/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:14:32 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/06 15:25:41 by nlaporte         ###   ########.fr       */
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
	if (button == 122)
	{
		env->plage.y1 += (tmp.x + tmp.y) / 40;
		env->plage.y2 += (tmp.x + tmp.y) / 40;
	}
	else if (button == 113)
	{
		env->plage.x1 += (tmp.x + tmp.y) / 40;
		env->plage.x2 += (tmp.x + tmp.y) / 40;
	}
	else if (button == 115)
	{
		env->plage.y1 -= (tmp.x + tmp.y) / 40;
		env->plage.y2 -= (tmp.x + tmp.y) / 40;
	}
	else if (button == 100)
	{
		env->plage.x1 -= (tmp.x + tmp.y) / 40;
		env->plage.x2 -= (tmp.x + tmp.y) / 40;
	}
}

static t_env	switch_anti(t_env *env)
{
	t_env	new;

	new = create_from_env(env);
	if (env->img)
		mlx_destroy_image(env->mlx, env->img);
	if (env->antialiasing)
		mlx_destroy_image(env->mlx, env->img_r);
	return (new);
}

int	keyboard_handler(int button, t_env *env)
{
	if (button == 65307)
		clear_env(env);
	check_move(button, env);
	if (button == 65362 && env->itelimit < 3000)
		env->itelimit += 10;
	else if (button == 65364 && env->itelimit > 10)
		env->itelimit -= 10;
	else if (button == 97)
		*env = switch_anti(env);
	render(env);
	return (0);
}
