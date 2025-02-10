/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssaa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:53:13 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/06 12:07:42 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fractol.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#define LIMIT 100


int	get_new_color(t_env *env, t_coord a)
{
	t_coord		t;
	t_coord3	tmp_color;
	t_coord3	color;
	int			diviseur;

	t = (t_coord){0, 0};
	color = (t_coord3){0, 0, 0};
	diviseur = 0;
	while (t.x < env->ssaa_coef && t.x + a.x < env->size.x)
	{
		t.y = 0;
		while (t.y < env->ssaa_coef && t.y + a.y < env->size.y)
		{
			tmp_color = get_pixel_color(env, env->addr, t.x + a.x, t.y + a.y);
			color = add_vec3(color, tmp_color);
			diviseur++;
			t.y++;
		}
		t.x++;
	}
	color = div_vec3(color, diviseur);
	return (rgba_to_hex(color.x, color.y, color.z, 255));
}

static void	*antialiasing_ssaa2(void *arg)
{
	t_argS *argu = (t_argS *)arg;
	t_coord	initY = {argu->litle.y, argu->big.y};
	t_coord	limit	= {argu->big.x ,\
		argu->big.y};
	int		color;
	int		pixel;

	while (argu->big.x < limit.x && argu->big.x <= argu->env.size.x)
	{
		argu->litle.y = initY.x;
		argu->big.y = initY.y;
		while (argu->big.y < limit.y && argu->env.size.y >= argu->big.y)
		{
			pixel = (argu->litle.y * argu->env.line_length_r) + (argu->litle.x * 4);
			color = get_new_color(&argu->env, argu->big);
			put_color(argu->env.addr_r, color, pixel);
			argu->big.y += argu->env.ssaa_coef;
			argu->litle.y++;
		}
		argu->big.x += argu->env.ssaa_coef;
		argu->litle.x++;
	}
	free(arg);
	return NULL;
}
/*
void antialiasing_ssaa(t_env *env)
{
	t_coord big;
	t_coord litle;

	big = (t_coord){0, 0};
	litle = (t_coord){0, 0};

	int size_x = env->size.x;
	int size_y = env->size.y;
	int ssaa_coef = env->ssaa_coef;

	#pragma omp parallel for collapse(2)
	for (int i = 0; i < size_x; i++) {
		big.y = 0;
		litle.y = 0;
		for (int j = 0; j < size_y; j++) {
			t_argS *arg = malloc(sizeof(t_argS));
			arg->env = *env;
			arg->litle = litle;
			arg->big = big;
			antialiasing_ssaa2(arg);
			big.y+=ssaa_coef;
			litle.y++;
		}
		big.x+=ssaa_coef;
		litle.x++;
	}
}
*/
void	aantialiasing_ssaa(t_env *env)
{
	t_coord	big;
	t_coord	litle;

	big = (t_coord){0, 0};
	litle = (t_coord){0, 0};
	while (big.x < env->size.x)
	{
		big.y = 0;
		litle.y = 0;
		while (big.y < env->size.y )
		{
			t_argS *arg = malloc(sizeof(t_argS));
			arg->env = *env;
			arg->litle = litle;
			arg->big = big;
			antialiasing_ssaa2(arg);
			big.y += env->ssaa_coef * BLOCK_SIZE_SSAA;
			litle.y += BLOCK_SIZE_SSAA;
		}
		big.x += env->ssaa_coef * BLOCK_SIZE_SSAA;
		litle.x += BLOCK_SIZE_SSAA;
	}
}

void	*anti_applie_zone(void *av)
{
	t_argF *arg = (t_argF*)av;
	t_coord zone = arg->act;
	t_env *env = &arg->env;
	t_coord limit = {zone.x + LIMIT * env->ssaa_coef, zone.y + LIMIT * env->ssaa_coef};

	while (zone.x < limit.x && zone.x < env->size.x)
	{
		zone.y = arg->act.y;
		while (zone.y < limit.y && zone.y < env->size.y)
		{
			int pixel = ( (zone.y / env->ssaa_coef) * env->line_length_r) + ((zone.x / env->ssaa_coef) * 4);
			int color = get_new_color(env, zone);
			put_color(env->addr_r, color, pixel);
			zone.y += env->ssaa_coef;
		}
		zone.x += env->ssaa_coef;
	}
	free(av);
	return NULL;
}

void	antialiasing_ssaa(t_env *env)
{
	t_coord	act = {0, 0};
	pthread_t thread[PROC + 1];
	int i = 0, j = 0;

	while (act.x < env->size.x)
	{
		act.y = 0;
		while (act.y < env->size.y)
		{
			t_argF *arg = malloc(sizeof(t_argF));
			arg->env = *env;
			arg->act = act;
			if (i >= PROC - 1)
			{
				j = 0;
				while (j < i)
					pthread_join(thread[j++], NULL);
				i = 0;
			}
			pthread_create(&thread[i++], NULL, anti_applie_zone, arg);
			act.y += LIMIT;
		}
		act.x += LIMIT;
	}
	j = 0;
	while (j < i)
		pthread_join(thread[j++], NULL);
}
