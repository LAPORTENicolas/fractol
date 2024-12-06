/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:49:43 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/06 15:32:20 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <libft.h>
# include <stdio.h>
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

typedef struct s_n_point
{
	t_coord	p1;
	t_coord	p2;
	t_coord	p3;
}	t_n_point;

typedef struct s_env
{
	void		(*type)(struct s_env*, t_coord);
	t_coord		julia_target;
	t_coord		z;
	t_coord3	size;
	t_coord3	(*palette)(double);
	t_coord4	pos;
	t_coord4	plage;
	t_zoom		zoom;
	void		*img;
	void		*img_r;
	void		*mlx;
	void		*win;
	char		**av;
	char		*addr;
	char		*addr_r;
	int			itelimit;
	int			default_ssaa;
	int			limit;
	int			bits_per_pixel;
	int			bits_per_pixel_r;
	int			line_length;
	int			line_length_r;
	int			endian;
	int			endian_r;
	int			shift;
	int			cam;
	int			julia_anim;
	int			antialiasing;
	int			ac;
	int			mouse_x;
	int			mouse_y;
	int			ssaa_coef;
	double		camscale;
	double		tik;
}				t_env;

void	save_image_to_bmp(void *img, void *mlx, int width, int height, char *filename);

t_env	create_from_env(t_env *env);

t_coord3	palette(double t);
t_coord3	palette2(double t);
t_coord3	palette3(double t);
t_coord3	palette4(double t);
t_coord3	palette5(double t);
t_coord3	palette6(double t);
t_coord3	palette7(double t);
t_coord3	get_pixel_color(t_env *env, char *addr, int x, int y);

void		render(t_env *env);
void		mandelbrot(t_env *env, t_coord act);
void		buddhabrot(t_env *env, t_coord act);
void		burning_ship(t_env *env, t_coord act);
void		newton(t_env *env, t_coord act);
void		nova(t_env *env, t_coord act);
void		julia(t_env *env, t_coord act);
int			anime_julia(t_env *env);
void		init_anime_julia(t_env *env);
void		print_help(void);
void		put_color(char *addr, int color, int pixel);
void		antialiasing_ssaa(t_env *env);
void		edit_env(t_env *env, int win);
void		clean_img(t_env *env);
void		clear_env(t_env *env);

t_env		create_env(void);

double		ft_atof(char *s);
double		ft_length(t_coord x);
double		ft_min(double x, double y);

t_coord		complex_subtract(t_coord c1, t_coord c2);
t_coord		complex_add(t_coord c1, t_coord c2);
t_coord		complex_mul(t_coord c1, t_coord c2);
t_coord		complex_div(t_coord c1, t_coord c2);

int			ft_smoothscroll(t_env *env);
int			rgba_to_hex(int r, int g, int b, int a);
int			configure_ssaa(t_env *env, char *s);
int			mouse_handler(int button, int x, int y, t_env *env);
int			args_manager(int ac, char **av, t_env *env);
int			keyboard_handler(int button, t_env *env);
int			configure_color(t_env *env, char *s);
int			configure_limit(t_env *env, char *s);
int			configure_itelimit(t_env *env, char *s);
int			configure_z(t_env *env, char *s1, char *s2);
int			rgba_fusion(t_coord4 a, t_coord4 b);
int			configure_set(t_env *env, char *s);
int			check_z(int ac, char **av, t_env *env, int i);
int			gen_color(t_env *env, t_coord3 i);

t_coord		add_vec2(t_coord vec1, t_coord vec2);
t_coord		sub_vec2(t_coord vec1, t_coord vec2);
t_coord		div_vec2(t_coord vec1, t_coord vec2);
t_coord		mul_vec2(t_coord vec1, t_coord vec2);
t_coord		init_vec2(double x, double y);
t_coord3	add_vec3(t_coord3 vec1, t_coord3 vec2);
t_coord3	umul_vec3(t_coord3 vec1, double m);
t_coord3	mul_vec3(t_coord3 vec1, t_coord3 vec2);
t_coord3	div_vec3(t_coord3 vec1, int div);
t_coord4	rgba(int r, int g, int b, int a);
t_coord4	sub_vec4(t_coord4 vec1, t_coord4 vec2);
t_coord4	udiv_vec4(t_coord4 vec1, int div);

#endif
