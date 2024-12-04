/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:49:43 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/04 14:07:10 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <libft.h>
# include <math.h>
# include <limits.h>
# define TWOP 6.28318530718

typedef struct s_coord
{
	double	x;
	double	y;
}				t_coord;

typedef struct s_coord3
{
	double	x;
	double	y;
	double	z;
}				t_coord3;

typedef struct s_coord4
{
	double	x1;
	double	x2;
	double	y1;
	double	y2;
}				t_coord4;

typedef struct s_zoom
{
	t_coord	neww;
	int		is_zoom;
	double	target;
	double	act;
	double	step;
}				t_zoom;

typedef struct s_env
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	t_coord		z;
	t_coord4	pos;
	t_coord3	size;
	t_coord4	plage;
	int			itelimit;
	int			limit;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			shift;
	int			cam;
	int			julia_anim;
	t_coord		julia_target;
	double		camscale;
	double		tik;
	int			mouse_x;
	int			mouse_y;
	t_zoom		zoom;
	void		(*type)(struct s_env*, t_coord);
	t_coord3	(*palette)(double);
}				t_env;

t_coord3	palette(double t);
t_coord3	palette2(double t);
t_coord3	palette3(double t);
t_coord3	palette4(double t);
t_coord3	palette5(double t);
t_coord3	palette6(double t);
t_coord3	palette7(double t);

void		render(t_env *env);
void		mandelbrot(t_env *env, t_coord act);
void		buddhabrot(t_env *env, t_coord act);
void		burning_ship(t_env *env, t_coord act);
void		nova_logic(t_env *env, t_coord act);
void		julia(t_env *env, t_coord act);
void		anime_julia(t_env *env);
void		init_anime_julia(t_env *env);
void		print_help(void);
void		put_color(t_env *env, int color, int pixel);

double		ft_atof(char *s);

int			ft_smoothscroll(t_env *env);
int			rgba_to_hex(int r, int g, int b, int a);
int			mouse_handler(int button, int x, int y, t_env *env);
int			args_manager(int ac, char **av, t_env *env);
int			keyboard_handler(int button, t_env *env);
int			configure_color(t_env *env, char *s);
int			configure_limit(t_env *env, char *s);
int			configure_itelimit(t_env *env, char *s);
int			configure_z(t_env *env, char *s1, char *s2);
int			rgba_fusion(t_coord4 a, t_coord4 b);

t_coord		add_vec2(t_coord vec1, t_coord vec2);
t_coord		sub_vec2(t_coord vec1, t_coord vec2);
t_coord		div_vec2(t_coord vec1, t_coord vec2);
t_coord		mul_vec2(t_coord vec1, t_coord vec2);
t_coord		init_vec2(double x, double y);
t_coord3	add_vec3(t_coord3 vec1, t_coord3 vec2);
t_coord3	umul_vec3(t_coord3 vec1, double m);
t_coord3	mul_vec3(t_coord3 vec1, t_coord3 vec2);
t_coord4	rgba(int r, int g, int b, int a);
t_coord4	sub_vec4(t_coord4 vec1, t_coord4 vec2);
t_coord4	udiv_vec4(t_coord4 vec1, int div);

#endif
