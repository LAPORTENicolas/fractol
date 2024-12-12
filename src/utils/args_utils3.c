/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:39:38 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/09 12:41:43 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fractol.h"

int	configure_size(char *s, t_env *env)
{
	int	res;

	if (!s)
		return (-1);
	res = atoi(s);
	if (res <= 50 || res >= 300)
		return (-1);
	env->default_size = res;
	return (0);
}
