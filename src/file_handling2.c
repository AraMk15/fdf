/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 15:56:11 by armkrtch          #+#    #+#             */
/*   Updated: 2025/07/29 21:40:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

char	*get_file(int fd, t_data *data)
{
	char	*line;
	char	*file;
	int		cols;

	line = "";
	file = malloc(sizeof(char));
	if (file == NULL)
		return (NULL);
	file[0] = '\0';
	data->map->y_dim = 0;
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (line != NULL)
		{
			cols = count_cols(line);
			if (!lines_consistent(cols, data))
				return (NULL);
			data->map->x_dim = cols;
			data->map->y_dim += 1;
			append_line_to_file(&line, &file);
		}
	}
	return (file);
}

int	lines_consistent(int cols, t_data *data)
{
	if (data->map->y_dim != 0 && data->map->x_dim != cols)
	{
		ft_putstr_fd("Found wrong line length. Exiting.\n", 2);
		return (0);
	}
	return (1);
}

void	append_line_to_file(char **line, char **file)
{
	char	*tmp;

	tmp = *file;
	*file = ft_strjoin(tmp, *line);
	free(tmp);
	free(*line);
	*line = "";
}

void	set_xy_min_max(t_map *map)
{
	t_pt	*cur;
	int		i;

	i = 0;
	while (i < map->x_dim * map->y_dim)
	{
		cur = map->pt_arr + i;
		if (cur->x < map->min_x)
			map->min_x = cur->x;
		if (cur->x > map->max_x)
			map->max_x = cur->x;
		if (cur->y < map->min_y)
			map->min_y = cur->y;
		if (cur->y > map->max_y)
			map->max_y = cur->y;
		i++;
	}
}

void	autoscale(t_map *map)
{
	float_t	scale_x;
	float_t	scale_y;

	map->min_x = 0;
	map->max_x = 0;
	map->min_y = 0;
	map->max_y = 0;
	set_xy_min_max(map);
	scale_x = (WIN_W / 2 - 30) / fmaxf(abs(map->max_x), abs(map->min_x));
	scale_y = (WIN_H / 2 - 30) / fmaxf(abs(map->max_y), abs(map->min_y));
	zoom(map, fminf(scale_x, scale_y));
}
