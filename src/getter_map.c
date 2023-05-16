/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yback <yback@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:38:03 by yback             #+#    #+#             */
/*   Updated: 2023/05/16 14:24:00 by yback            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	yb_map_check_split(char *map_line)
{
	char	**splitted_map;
	int		line_size;
	int		i;
	int		error_check;

	i = -1;
	error_check = 0;
	splitted_map = ft_split(map_line, ' ');
	while (splitted_map[++i])
	{
		line_size = ft_strlen(splitted_map[i]);
		if (splitted_map[i][0] == '0' || splitted_map[i][line_size - 1] == '0')
		{
			error_check = -1;
			break ;
		}
	}
	free_arr(splitted_map);
	return (error_check);
}

int	yb_wall_check(t_map *yback_map, int i, int j)
{
	char	u;
	char	d;

	if (i == 0 || i == yback_map->map_height - 1)
		return (-1);
	else
	{
		u = yback_map->map[i - 1][j];
		d = yback_map->map[i + 1][j];
		if (!(u == 'N' || u == 'S' || u == 'E' || u == 'W'
				|| u == '1' || u == '0'))
			return (-1);
		if (!(d == '1' || d == '0' || d == 'N' || d == 'S'
				|| d == 'E' || d == 'W'))
			return (-1);
	}
	return (0);
}

int	yb_check_info(t_map *yback_map)
{
	if (yb_strslen(yback_map->map) <= 1)
		return (-1);
	return (0);
}
