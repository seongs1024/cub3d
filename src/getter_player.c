/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yback <yback@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:40:06 by yback             #+#    #+#             */
/*   Updated: 2023/05/05 19:40:30 by yback            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	yb_find_player_pos(t_map *yback_map, int i, int j)
{
	char	c;

	c = yback_map->map[i][j];
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		if (yback_map->player_pos[0] > 0)
			return (-1);
		yback_map->player_dir = c;
		yback_map->player_pos[0] = i;
		yback_map->player_pos[1] = j;
		return (yb_wall_check(yback_map, i, j));
	}
	else if (!(c == '1' || c == '0' || c == ' '))
		return (-1);
	else if (c == '0')
		return (yb_wall_check(yback_map, i, j));
	return (0);
}

int	yb_find_player(t_map *yback_map)
{
	int	i;
	int	j;
	int	error_check;
	
	i = 0;
	error_check = 0;
	while (yback_map->map[i])
	{
		error_check = yb_map_check_split(yback_map->map[i]);
		if (error_check == -1)
			return (-1);
		j = 0;
		while (yback_map->map[i][j])
		{
			error_check = yb_find_player_pos(yback_map, i, j);
			if (error_check == -1)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}