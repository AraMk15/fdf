/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:03:11 by armkrtch          #+#    #+#             */
/*   Updated: 2025/07/29 21:40:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	rotate_x(t_map *map, float_t angle)
{
	t_matrix3x3	rot_x;

	rot_x = (t_matrix3x3){
		1, 0, 0,
		0, cos(angle), -sin(angle),
		0, sin(angle), cos(angle)};
	transform_map(map, rot_x);
}

void	rotate_y(t_map *map, float_t angle)
{
	t_matrix3x3	rot_y;

	rot_y = (t_matrix3x3){
		cos(angle), 0, sin(angle),
		0, 1, 0,
		-sin(angle), 0, cos(angle)};
	transform_map(map, rot_y);
}

void	generate_iso_view(t_map *map)
{
	rotate_x(map, -M_PI_2);
	rotate_y(map, M_PI_4);
	rotate_x(map, ISO);
}
