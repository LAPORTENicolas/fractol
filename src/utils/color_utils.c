/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:07:15 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/01 00:13:37 by nlaporte         ###   ########.fr       */
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

t_coord4	rgba(int r, int g, int b, int a)
{
	t_coord4	rgbaa;

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
	rgbaa.x1 = r;
	rgbaa.x2 = g;
	rgbaa.y1 = b;
	rgbaa.y2 = a;
	return (rgbaa);
}

void	put_color(t_env *env, int color, int pixel)
{
	env->addr[pixel + 0] = (color) & 0xFF;
	env->addr[pixel + 1] = (color >> 8) & 0xFF;
	env->addr[pixel + 2] = (color >> 16) & 0xFF;
	env->addr[pixel + 3] = (color >> 24);
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
