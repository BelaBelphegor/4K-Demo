/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metaball.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 18:27:07 by tiboitel          #+#    #+#             */
/*   Updated: 2017/02/03 18:43:45 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaball.h"

int		metaball_init(t_metaball *metaball, float x, float y, float radius)
{
	metaball->_x = x;
	metaball->_y = y;
	metaball->_radius = radius;
	return (1);
}

float	metaball_equation(t_metaball *metaball, float x, float y)
{
	return (metaball->_radius / sqrt((x - metaball->_x) * (x - metaball->_x)
		+ (y - metaball->_y) * (y - metaball->_y)));
}
