/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_helpears.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:02:11 by armkrtch          #+#    #+#             */
/*   Updated: 2025/07/29 21:40:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_pt	mat_mult(t_matrix3x3 mat, t_pt pt)
{
	t_pt	res;

	res.x = pt.x * mat.c1r1 + pt.y * mat.c2r1 + pt.z * mat.c3r1;
	res.y = pt.x * mat.c1r2 + pt.y * mat.c2r2 + pt.z * mat.c3r2;
	res.z = pt.x * mat.c1r3 + pt.y * mat.c2r3 + pt.z * mat.c3r3;
	res.color = pt.color;
	return (res);
}

t_pt	vec_add(t_pt pt1, t_pt pt2)
{
	t_pt	sum;

	sum.x = pt1.x + pt2.x;
	sum.y = pt1.y + pt2.y;
	sum.z = pt1.z + pt2.z;
	sum.color = pt1.color;
	return (sum);
}

t_pt	vec_sub(t_pt pt1, t_pt pt2)
{
	t_pt	diff;

	diff.x = pt1.x - pt2.x;
	diff.y = pt1.y - pt2.y;
	diff.z = pt1.z - pt2.z;
	diff.color = pt1.color;
	return (diff);
}

void	zoom(t_map *map, float_t factor)
{
	t_matrix3x3	scale;

	scale = (t_matrix3x3){factor, 0, 0, 0, factor, 0, 0, 0, factor};
	transform_map(map, scale);
}

t_map	*transform_map(t_map *map, t_matrix3x3 mat)
{
	int		i;
	t_pt	*cur;

	i = 0;
	while (i < map->x_dim * map->y_dim)
	{
		cur = map->pt_arr + i;
		*cur = mat_mult(mat, *cur);
		i++;
	}
	map->base_i = mat_mult(mat, map->base_i);
	map->base_j = mat_mult(mat, map->base_j);
	map->base_k = mat_mult(mat, map->base_k);
	return (map);
}
