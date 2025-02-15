/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:56:58 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/09 12:41:11 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	no_arg(char **av, t_env *env, int i)
{
	if (ft_strncmp(av[i], "-shift", ft_strlen("-shift") + 1) == 0)
		env->shift = 1;
	else if (ft_strncmp(av[i], "-h", ft_strlen("-h") + 1) == 0)
	{
		print_help();
		exit(EXIT_SUCCESS);
	}
	else if (ft_strncmp(av[i], "-debug", ft_strlen("-debug") + 1) == 0)
		env->print_debug = 1;
	else
		return (-1);
	return (0);
}

int	one_arg2(int ac, char **av, t_env *env, int i)
{
	if (ft_strncmp(av[i], "-size", ft_strlen("-size") + 1) == 0)
	{
		if (i + 1 < ac && configure_size(av[i + 1], env) == 0)
			return (0);
	}
	return (-1);
}

int	one_arg(int ac, char **av, t_env *env, int i)
{
	if (ft_strncmp(av[i], "-itel", ft_strlen("-itel") + 1) == 0)
	{
		if (i + 1 < ac && configure_itelimit(env, av[++i]) == 0)
			return (0);
	}
	else if (ft_strncmp(av[i], "-c", ft_strlen("-c") + 1) == 0)
	{
		if (i + 1 < ac && configure_color(env, av[++i]) == 0)
			return (0);
	}
	else if (ft_strncmp(av[i], "-l", ft_strlen("-l") + 1) == 0)
	{
		if (i + 1 < ac && configure_limit(env, av[++i]) == 0)
			return (0);
	}
	else if (ft_strncmp(av[i], "-x", ft_strlen("-x") + 1) == 0)
	{
		if (i + 1 < ac && configure_ssaa(env, av[++i]) == 0)
			return (0);
	}
	else if (one_arg2(ac, av, env, i) == 0)
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
		else if (check_z(ac, av, env, i) == 0)
			i += 3;
		else if (one_arg(ac, av, env, i) == 0)
			i += 2;
		else if (no_arg(av, env, i) == 0)
			i++;
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
		ft_printf("\033[31mError bad argument, try ./fractol -h\033[0m");
		return (-1);
	}
	else if (status == 1)
	{
		print_help();
		return (-1);
	}
	return (0);
}
