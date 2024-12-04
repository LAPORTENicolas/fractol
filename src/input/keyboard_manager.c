/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:14:32 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/04 11:21:26 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fractol.h"

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

int	keyboard_handler(int button, t_env *env)
{
	if (button == 65307)
		exit(EXIT_SUCCESS);
	check_move(button, env);
	if (button == 65362)
		env->itelimit += 10;
	else if (button == 65364)
		env->itelimit -= 10;
	render(env);
	return (0);
}
