/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:38:21 by nlaporte          #+#    #+#             */
/*   Updated: 2025/01/28 20:39:18 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fractol.h"

void	optional_keys2(int button, t_env *env)
{
	if (env->paletteid == 6 && button == 108)
		env->paletteid = 1;
	else if (button == 108)
		env->paletteid++;
	if (env->paletteid == 1 && button == 107)
		env->paletteid = 6;
	else if (button == 107)
		env->paletteid--;
	if (env->paletteid == 1)
		env->palette = palette;
	if (env->paletteid == 2)
		env->palette = palette2;
	if (env->paletteid == 3)
		env->palette = palette3;
	if (env->paletteid == 4)
		env->palette = palette4;
	if (env->paletteid == 5)
		env->palette = palette5;
	if (env->paletteid == 6)
		env->palette = palette6;
}
