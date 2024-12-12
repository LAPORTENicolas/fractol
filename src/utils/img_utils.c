/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 22:25:14 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/10 23:43:39 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fractol.h"

static t_buddha	get_win(t_env *env)
{
	t_buddha	new;

	new.img = mlx_new_image(env->mlx, env->size.x, env->size.y);
	new.addr = mlx_get_data_addr(new.img, \
	&new.bits_per_pixel, &new.line_length, &new.endian);
	return (new);
}

static void	update_img(t_env *env, t_buddha *new)
{
	env->addr = new->addr;
	env->img = new->img;
	env->line_length = new->line_length;
	env->endian = new->endian;
	env->bits_per_pixel = new->bits_per_pixel;
}

void	rotate_buddha(t_env *env)
{
	t_coord		i;
	t_buddha	new;
	t_coord3	c;
	int			pixel;

	new = get_win(env);
	i.x = 0;
	while (i.x < env->size.x)
	{
		i.y = 0;
		while (i.y < env->size.y)
		{
			c = get_pixel_color(env, env->addr, i.y, i.x);
			pixel = (i.y * env->line_length) + (i.x * 4);
			put_color(new.addr, rgba_to_hex(c.x, c.y, c.z, 255), pixel);
			i.y++;
		}
		i.x++;
	}
	update_img(env, &new);
}
