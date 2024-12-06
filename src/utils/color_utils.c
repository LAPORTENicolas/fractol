/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:07:15 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/06 14:16:01 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fractol.h"

int	rgba_to_hex(int r, int g, int b, int a)
{
	if (r < 0)
		r = 0;
	if (r > 255)
		r = 255;
	if (g < 0)
		g = 0;
	if (g > 255)
		g = 255;
	if (b < 0)
		b = 0;
	if (b > 255)
		b = 255;
	if (a < 0)
		a = 0;
	if (a > 255)
		a = 255;
	return ((a << 24) | (r << 16) | (g << 8) | b);
}

int	gen_color(t_env *env, t_coord3 i)
{
	t_coord3	pal;
	double		logg;
	double		smooth;

	logg = log(i.z) / 2.0;
	if (env->shift)
		smooth = (i.x + 1 + env->tik) - log(logg) / log(2.0);
	else
		smooth = i.x + 1 - log(logg) / log(2.0);
	pal = env->palette(smooth / (double)env->itelimit);
	return (rgba_to_hex(pal.x * 255, pal.y * 255, pal.z * 255, 255));
}

t_coord3	get_pixel_color(t_env *env, char *addr, int x, int y)
{
	t_coord3	color;
	int			pixel;

	pixel = (y * env->line_length) + (x * 4);
	color.x = (unsigned char)addr[pixel + 2];
	color.y = (unsigned char)addr[pixel + 1];
	color.z = (unsigned char)addr[pixel];
	return (color);
}

void	put_color(char *addr, int color, int pixel)
{
	addr[pixel + 0] = (color) & 0xFF;
	addr[pixel + 1] = (color >> 8) & 0xFF;
	addr[pixel + 2] = (color >> 16) & 0xFF;
	addr[pixel + 3] = (color >> 24);
}

int	rgba_fusion(t_coord4 a, t_coord4 b)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	bl;

	r = (unsigned char)((b.x1 * b.y2 + a.x1 * (255 - b.y2)) / 255.0);
	g = (unsigned char)((b.x2 * b.y2 + a.x2 * (255 - b.y2)) / 255.0);
	bl = (unsigned char)((b.y1 * b.y2 + a.y1 * (255 - b.y2)) / 255.0);
	return (((int)b.y2 << 24) | (r << 16) | (g << 8) | bl);
}
