/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yback <yback@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:36:00 by yback             #+#    #+#             */
/*   Updated: 2023/05/05 19:38:20 by yback            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	yb_init_colors(t_map *yback_map, int *colors, char **spl_color)
{
	yback_map->flag++;
	colors[0] = yb_atoi_check(spl_color[0]);
	colors[1] = yb_atoi_check(spl_color[1]);
	colors[2] = yb_atoi_check(spl_color[2]);
}

int	yb_color_check(int *colors)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (colors[i] == -123)
			return (-1);
	}
	return (0);
}

int	yb_color_init(char **spl_line, t_map *yback_map)
{
	char	**spl_color;
	int		error_check;

	error_check = 0;
	spl_color = ft_split(spl_line[1], ',');
	if (yb_check_int(spl_color) == -1 || yb_strslen(spl_color) != 3)
	{
		free_arr(spl_color);
		return (-1);
	}
	if (yb_strcmp(spl_line[0], "F") == 1)
		yb_init_colors(yback_map, yback_map->f_colors, spl_color);
	else if (yb_strcmp(spl_line[0], "C") == 1)
		yb_init_colors(yback_map, yback_map->c_colors, spl_color);
	if (yb_color_check(yback_map->f_colors) == -1
		|| yb_color_check(yback_map->c_colors) == -1)
		error_check = -1;

	free_arr(spl_color);
	return (error_check);
}