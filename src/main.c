/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:01:11 by armkrtch          #+#    #+#             */
/*   Updated: 2025/07/29 21:40:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./fdf MAPFILE\n", 2);
		return (-1);
	}
	if (parse_file(&data, argv[1]) == -1)
		return (-1);
	generate_map(&data);
	generate_iso_view(data.map);
	autoscale(data.map);
	data.animate_on = 0;
	if (start_mlx(&data) == -1)
		return (-1);
	return (0);
}
