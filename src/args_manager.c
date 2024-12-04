/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:56:58 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/04 14:09:04 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"
#include <libft.h>

int	configure_set(t_env *env, char *s)
{
	if (s && ft_strncmp(s, "mandelbrot", ft_strlen("mandelbrot") + 1) == 0)
	{
		env->type = mandelbrot;
		return (0);
	}
	else if (s && ft_strncmp(s, "julia", ft_strlen("julia") + 1) == 0)
	{
		env->type = julia;
		return (0);
	}
	else if (s && ft_strncmp(s, "burning-ship", ft_strlen("burning-ship") + 1) == 0)
	{
		env->type = burning_ship;
		return (0);
	}
	else if (s && ft_strncmp(s, "buddhabrot", ft_strlen("buddhabrot") + 1) == 0)
	{
		env->type = buddhabrot;
		return (0);
	}
	else if (s && ft_strncmp(s, "nova", ft_strlen("nova") + 1) == 0)
	{
		env->type = nova_logic;
		return (0);
	}
	ft_putendl_fd("\033[31mType error:\
	bad name, try ./fractol -t mandelbrot\033[0m", 2);
	return (-1);
}

int	test(int ac, char **av, t_env *env, int i)
{
	if (ft_strncmp(av[i], "-itel", ft_strlen("-itel") + 1) == 0)
	{
		if (i + 1 >= ac || configure_itelimit(env, av[++i]) == -1)
			return (-1);
	}
	else if (ft_strncmp(av[i], "-h", ft_strlen("-h") + 1) == 0)
		print_help();
	else if (ft_strncmp(av[i], "-c", ft_strlen("-c") + 1) == 0)
	{
		if (i + 1 >= ac || configure_color(env, av[++i]) == -1)
			return (-1);
	}
	else if (ft_strncmp(av[i], "-l", ft_strlen("-l") + 1) == 0)
	{
		if (i + 1 >= ac || configure_limit(env, av[++i]) == -1)
			return (-1);
	}
	else if (ft_strncmp(av[i], "-shift", ft_strlen("-shift") + 1) == 0)
		env->shift = 1;
	else if (ft_strncmp(av[i], "-anime", ft_strlen("-anime") + 1) == 0)
		init_anime_julia(env);
	return (0);
}

int	check_type(char **av, t_env *env, int i)
{
	if (configure_set(env, av[++i]) != -1)
		return (0);
	return (-1);
}

int	get_arg_val(int ac, char **av, t_env *env)
{
	int	status;
	int	i;

	status = -1;
	i = 1;
	while (i < ac)
	{
		if (ft_strncmp(av[i], "-t", ft_strlen("-t") + 1) == 0)
			status = check_type(av, env, i);
		else if (ft_strncmp(av[i], "-z", ft_strlen("-z") + 1) == 0)
		{
			if (i + 2 >= ac || configure_z(env, av[i + 1], av[i + 2]) == -1)
				return (-1);
			else
				i += 3;
		}
		else if (test(ac, av, env, i) == 0)
			i++;
		else
			return (-1);
		i++;
	}
	return (status);
}

int	args_manager(int ac, char **av, t_env *env)
{
	int	status;

	status = get_arg_val(ac, av, env);
	if (ac <= 1)
		return (-1);
	if (status == -1)
	{
		ft_putendl_fd("\033[31mError bad argument, try ./fractol -h\033[0m", 2);
		return (-1);
	}
	else if (status == 1)
	{
		print_help();
		return (-1);
	}
	return (0);
}
