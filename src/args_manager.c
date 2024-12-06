/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:56:58 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/06 13:38:44 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	no_arg(char **av, t_env *env, int i)
{
	if (ft_strncmp(av[i], "-shift", ft_strlen("-shift") + 1) == 0)
	{
		env->shift = 1;
		return (0);
	}
	else if (ft_strncmp(av[i], "-anime", ft_strlen("-anime") + 1) == 0)
	{
		init_anime_julia(env);
		return (0);
	}
	else if (ft_strncmp(av[i], "-h", ft_strlen("-h") + 1) == 0)
	{
		print_help();
		return (0);
	}
	else if (ft_strncmp(av[i], "-anti", ft_strlen("-anti") + 1) == 0)
	{
		env->antialiasing = 1;
		return (0);
	}
	return (-1);
}

int	one_arg(int ac, char **av, t_env *env, int i)
{
	if (ft_strncmp(av[i], "-itel", ft_strlen("-itel") + 1) == 0)
	{
		if (i + 1 >= ac || configure_itelimit(env, av[++i]) == -1)
			return (-1);
	}
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
	return (0);
}

int	check_type(char **av, t_env *env, int i)
{
	if (configure_set(env, av[i]) != -1)
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
		{
			status = check_type(av, env, i + 1);
			i += 2;
		}
		else if (no_arg(av, env, i) == 0)
			i++;
		else if (one_arg(ac, av, env, i) == 0)
			i += 2;
		else if (check_z(ac, av, env, i) == 0)
			i += 3;
		else
			return (-1);
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
