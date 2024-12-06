/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nova.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:09:40 by nlaporte          #+#    #+#             */
/*   Updated: 2024/12/06 13:10:09 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fractol.h"
#include <math.h>

static t_coord complex_pow(t_coord nb, double power)
{
    double r = sqrt(nb.x * nb.x + nb.y * nb.y);  // Calcul du module (|z|)
    double theta = atan2(nb.y, nb.x);  // Calcul de l'argument (l'angle) de z
    
    // Calcul de la nouvelle magnitude (module) : r^power
    double r_new = pow(r, power);
    
    // Calcul du nouvel argument (angle) : power * theta
    double theta_new = power * theta;
    
    // Conversion en coordonnées cartésiennes
    t_coord result;
    result.x = r_new * cos(theta_new);  // Partie réelle
    result.y = r_new * sin(theta_new);  // Partie imaginaire

    return result;
}
void nova_logic(t_env *env, t_coord act)
{
    t_coord c;
    t_coord z;
    int i;
    int color;
    t_coord p1 = {1.0, 0.0};
    t_coord p2 = {-.5, .866};
    t_coord p3 = {-.5, -.866};
    double limit = 0.1;
    double R = 0.5;
    double p = 3.0;
    t_coord decalage = {.1, .2};

    i = 0;
    c = init_vec2(act.x / env->size.z + env->plage.x1, act.y / env->size.z + env->plage.y1);
    z = init_vec2(0, 0);  // Initialisation de z

    double d_1 = ft_length(complex_subtract(c, p1));
    double d_2 = ft_length(complex_subtract(c, p2));
    double d_3 = ft_length(complex_subtract(c, p3));
    double d_min = ft_min(d_1, ft_min(d_2, d_3));

    while (d_min > limit && i < env->itelimit)
    {
        // Calcul de f et f' pour la fractale Nova
        t_coord f = complex_subtract(complex_pow(z, p), init_vec2(1.0, 0.0));
        t_coord f_prime = complex_mul((t_coord){p, 0}, complex_pow(z, p - 1));

        // Mise à jour de z avec la méthode de Newton
        z = complex_subtract(z, complex_mul((t_coord){R, 0}, complex_div(f, f_prime)));
        z = complex_add(z, decalage);

        // Calcul des nouvelles distances
        d_1 = ft_length(complex_subtract(c, p1));
        d_2 = ft_length(complex_subtract(c, p2));
        d_3 = ft_length(complex_subtract(c, p3));
        d_min = ft_min(d_1, ft_min(d_2, d_3));
        i++;
    }

    // Détermination de la couleur en fonction de l'itération
    if (i != env->itelimit)
    {
        color = rgba_to_hex(i * exp(-i / 10), (i * 2) % 255, (i * 3) % 255, 255);
    }
    else
    {
        color = rgba_to_hex(0, 0, 0, 255); // Changer la couleur noire opaque pour éviter la transparence
    }

    // Application de la couleur
    put_color(env->addr, color, (act.y * env->line_length) + (act.x * 4));
}void	nova(t_env *env, t_coord act)
{
	nova_logic(env, act);
	return ;
}
