/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buddhabrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:09:40 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/10 23:42:58 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fractol.h"
#include <libft.h>

t_coord3	**get_tmp_map(int x, int y)
{
	t_coord3	**res;
	int			i;
	int			j;

	res = malloc(sizeof(t_coord3 *) * x);
	if (!res)
		return (NULL);
	i = 0;
	while (i < x)
	{
		res[i] = malloc(sizeof(t_coord3) * y);
		if (!res[i])
			return (NULL);
		j = 0;
		while (j < y)
		{
			res[i][j].x = 0;
			res[i][j].y = 0;
			res[i][j++].z = 0;
		}
		i++;
	}
	return (res);
}

void	test(t_env *env, t_list *lst, t_coord3 **tmp_map, int i)
{
	t_coord3	elm;

	if (lst == NULL)
		return ;
	elm = *(t_coord3 *)lst->content;
	if (elm.x < 0 || elm.x >= env->size.x || elm.y < 0 || elm.y >= env->size.y)
		return ;
	if (i > 100)
		tmp_map[(int)elm.x][(int)elm.y].x += 1;
	if (i > 400)
		tmp_map[(int)elm.x][(int)elm.y].y += 1;
	if (i > 500)
		tmp_map[(int)elm.x][(int)elm.y].z += 1;
	test(env, lst->next, tmp_map, i);
}

void	buddhaconvertor(t_env *env, t_coord3 **tmp_map)
{
	t_coord3	tmp;
	t_coord		act;
	int			color;

	act.y = 0;
	while (act.y < env->size.y)
	{
		act.x = 0;
		while (act.x < env->size.x - 1)
		{
			printf("act: x:%f y:%f\n", act.x, act.y);
			tmp = tmp_map[(int)act.x][(int)act.y];
			color = rgba_to_hex(tmp.x, tmp.y, tmp.z, 255);
			put_color(env->addr, color, \
			(act.y * env->line_length) + (act.x * 4));
			act.x++;
		}
		act.y++;
	}
}

static int	buddhabrot_logic(t_env *env, t_coord act, \
t_coord3 **tmp_map, t_list *lst)
{
	t_coord		c;
	double		tmp;
	t_coord		z;
	int			i;

	c = (t_coord){act.x / env->size.z + env->plage.x1, \
	act.y / env->size.z + env->plage.y1};
	z = (t_coord){0, 0};
	i = 0;
	while (z.x * z.x + z.y * z.y < env->limit && i < env->itelimit)
	{
		tmp = z.x;
		z.x = z.x * z.x - z.y * z.y + c.x;
		z.y = 2 * z.y * tmp + c.y;
		i++;
		ft_lstadd_back(&lst, ft_lstnew(\
		(void *)(&(t_coord){(z.x - env->plage.x1) * env->size.z, \
		(z.y - env->plage.y1) * env->size.z})));
	}
	if (i != env->limit)
	{
		test(env, lst, tmp_map, i);
	}
	return (i);
}

void	buddhabrot(t_env *env, t_coord act, t_coord3 **tmp_map)
{
	t_list	*lst;

	lst = ft_lstnew((void *)(&(t_coord){0, 0}));
	buddhabrot_logic(env, act, tmp_map, lst);
	if (lst != NULL)
	{
		ft_lstclear(&lst, NULL);
		free(lst);
	}
	return ;
}
