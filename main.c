/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:08:35 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/04 12:41:42 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <libft.h>
#include <mlx.h>
#include <stdio.h>

int	loop_hook(t_env *env)
{
	if (env->zoom.is_zoom)
		ft_smoothscroll(env);
	render(env);
	return (0);
}

int	get_new_color(t_env *env, t_coord act)
{
	t_coord		tmp;
	t_coord3	tmp_color;
	t_coord3	color;
	int		diviseur;

	tmp = (t_coord){0, 0};
	color = (t_coord3){0, 0, 0};
	diviseur = 0;
	while (tmp.x < ANTI && tmp.x + act.x < env->size.x)
	{
		tmp.y = 0;
		while (tmp.y < ANTI + 1 && tmp.y + act.y < env->size.y)
		{
			tmp_color = get_pixel_color(env, env->addr, tmp.x + act.x, tmp.y + act.y);
			color.x += tmp_color.x;
			color.y += tmp_color.y;
			color.z += tmp_color.z;
			diviseur++;
			tmp.y++;
		}
		tmp.x++;
	}
	color.x /= diviseur;
	color.y /= diviseur;
	color.z /= diviseur;
	return (rgba_to_hex(color.x, color.y, color.z, 255));
}

void	antialiasing(t_env *env)
{
	t_coord	big;
	t_coord	litle;
	int		color;

	big = (t_coord){0, 0};
	litle = (t_coord){0, 0};
	while (big.x < env->size.x)
	{
		big.y = 0;
		litle.y = 0;
		while (big.y < env->size.y)
		{
			color = get_new_color(env, big);
			put_color2(env->addr_r, color, (litle.y * env->line_length_r) + (litle.x * 4));
			big.y += ANTI;
			litle.y++;
		}
		big.x += ANTI;
		litle.x++;
	}
}

void	render(t_env *env)
{
	t_coord	act;

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
	env->tik += .4;
	if (env->antialiasing)
	{
		antialiasing(env);
		mlx_put_image_to_window(env->mlx, env->win, env->img_r, 0, 0);
		return ;
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}

t_env	create_env(void)
{
	t_env	env;

	env.plage.x1 = -2;
	env.plage.x2 = 2;
	env.plage.y1 = -2;
	env.plage.y2 = 2;
	env.itelimit = 100;
	env.z.x = 0.1;
	env.z.y = 0.7;
	env.tik = 0.;
	env.limit = 2;
	env.shift = 0;
	env.zoom.is_zoom = 0;
	env.pos = env.plage;
	env.type = NULL;
	env.palette = palette;
	env.mlx = mlx_init();
	return (env);
}

void edit_env(t_env *env)
{
	if (env->antialiasing)
	{
		env->size.z = 450;
		env->size.x = (env->plage.x2 - env->plage.x1) * env->size.z;
		env->size.y = (env->plage.y2 - env->plage.y1) * env->size.z;
		env->win = mlx_new_window(env->mlx, env->size.x / ANTI, env->size.y / ANTI, "Fractol");
	}
	else
	{
		env->size.z = 150;
		env->size.x = (env->plage.x2 - env->plage.x1) * env->size.z;
		env->size.y = (env->plage.y2 - env->plage.y1) * env->size.z;
		env->win = mlx_new_window(env->mlx, env->size.x, env->size.y, "Fractol");
	}
	env->img = mlx_new_image(env->mlx, env->size.x, env->size.y);
	env->addr = mlx_get_data_addr(env->img, &env->bits_per_pixel, \
		&env->line_length, &env->endian);
	// RENDU
	if (env->antialiasing)
	{
		env->img_r = mlx_new_image(env->mlx, env->size.x / ANTI, env->size.y / ANTI);
		env->addr_r = mlx_get_data_addr(env->img_r, &env->bits_per_pixel_r, \
		&env->line_length_r, &env->endian_r);
	}
}

double	ft_atof(char *s)
{
	double	atof;
	double	tmp;
	int		i;

	i = 10;
	atof = 0;
	if (s == NULL)
		return (0.);
	if (ft_isdigit(*s))
		atof += *s++ - '0';
	else
		return (0.);
	s++;
	while (*s && ft_isdigit(*s))
	{
		tmp = *s++ - '0';
		tmp /= i;
		atof += tmp;
		i *= 10;
	}
	return (atof);
}

int	main(int ac, char **av)
{
	t_env	env;

	env = create_env();
	env.antialiasing = 0;
	if (args_manager(ac, av, &env) != 0)
		return (-1);
	edit_env(&env);
	render(&env);
	mlx_hook(env.win, 4, 1L << 2, mouse_handler, &env);
	mlx_hook(env.win, 2, 5, keyboard_handler, &env);
	mlx_loop_hook(env.mlx, loop_hook, &env);
	mlx_loop(env.mlx);
	return (0);
}
