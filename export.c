/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:09:58 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/09 14:10:32 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <fcntl.h>
#include <libft.h>
#include <unistd.h>
#include <stdlib.h>
#include <mlx.h>

static void	get_header(int fd, int width, int height)
{
	int		filesize;
	char	header[54];

	filesize = 54 + 4 * width * height;
	ft_bzero(header, 54);
	header[0] = 'B';
	header[1] = 'M';
	*(int *)&header[2] = filesize;
	header[10] = 54;
	header[14] = 40;
	*(int *)&header[18] = width;
	*(int *)&header[22] = height;
	header[26] = 1;
	header[28] = 32;
	write(fd, header, 54);
}

static void	get_file(int fd, char *data, int width, int height)
{
	write(fd, data, 4 * width * height);
}

static int	put_nbr(t_env *env, char *str)
{
	char	*r;
	int		i;

	if (str == NULL)
		return (0);
	r = ft_itoa(env->screen_nb);
	if (r == NULL)
		return (0);
	i = 0;
	while (r[i])
		*str++ = r[i++];
	env->screen_nb++;
	return (i);
}

static void	get_name(t_env *env)
{
	char	name[50];
	int		i;

	i = 0;
	name[i++] = 'S';
	name[i++] = 'c';
	name[i++] = 'r';
	name[i++] = 'e';
	name[i++] = 'e';
	name[i++] = 'n';
	name[i++] = '-';
	i += put_nbr(env, &name[7]);
	name[i++] = '.';
	name[i++] = 'b';
	name[i++] = 'm';
	name[i++] = 'p';
	name[i++] = '\0';
	if (env->file_name)
		free(env->file_name);
	env->file_name = ft_strdup(name);
}

void	screen_shot(t_env *env, void *img, int width, int height)
{
	t_screen	data_o;
	int			fd;
	char		*data;

	data = mlx_get_data_addr(img, &data_o.bpp, \
	&data_o.line_length, &data_o.endian);
	get_name(env);
	fd = open(env->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		return ;
	}
	get_header(fd, width, height);
	get_file(fd, data, width, height);
	close(fd);
}
