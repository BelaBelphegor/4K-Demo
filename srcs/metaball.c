/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metaball.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 18:27:07 by tiboitel          #+#    #+#             */
/*   Updated: 2019/04/23 18:18:47 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaball.h"

int		metaball_init(t_metaball *metaball, float x, float y, float radius, int dir_x, int dir_y, int speed)
{
	metaball->_x = x;
	metaball->_y = y;
	metaball->_radius = radius;
	metaball->_dir_x = dir_x;
	metaball->_dir_y = dir_y;
	metaball->_speed = speed;
	metaball_random_color(metaball);
	return (1);
}

float	metaball_equation(t_metaball *metaball, float x, float y)
{
	return (metaball->_radius / sqrt((x - metaball->_x) * (x - metaball->_x)
		+ (y - metaball->_y) * (y - metaball->_y)));
}

void	metaball_random_color(t_metaball *metaball)
{
	int		random;
	int		colors[5];
	
	random = rand() % 4;
	colors[0] = 0x2256F2;
	colors[1] = 0x417CF2;
	colors[2] = 0x3DADF2;
	colors[3] = 0x3DD1F2;
	colors[4] = 0x4BF2F2;
	metaball->_color = colors[random];
}
