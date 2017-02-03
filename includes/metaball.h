/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metaballs.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 18:23:19 by tiboitel          #+#    #+#             */
/*   Updated: 2017/02/03 18:46:48 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef METABALL_H
# define METABALL_H
# include <math.h>

typedef struct	s_metaball
{
	float		_x;
	float		_y;
	float		_radius;
}				t_metaball;

int				metaball_init(t_metaball *metaball, float x, float y, float radius);
float			metaball_equation(t_metaball *metaball, float x, float y);
#endif
