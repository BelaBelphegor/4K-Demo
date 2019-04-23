/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metaballs.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 18:23:19 by tiboitel          #+#    #+#             */
/*   Updated: 2019/04/23 18:19:01 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef METABALL_H
# define METABALL_H

# include <math.h>
# include <stdlib.h>

typedef struct	s_metaball
{
	float		_x;
	float		_y;
	float		_radius;
	int			_dir_x;
	int			_dir_y;
	float		_speed;
	int			_color;
}				t_metaball;

int				metaball_init(t_metaball *metaball, float x, float y, float radius, int dir_x, int dir_y,
		int speed);
float			metaball_equation(t_metaball *metaball, float x, float y);
void			metaball_random_color(t_metaball *metaball);
#endif
